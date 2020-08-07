#include <QVariantList>
#include <QObject>
#include <memory>
#include <QVector2D>
#include <QVector3D>
#include "Environment.hpp"
#include <definitions.hpp>

void Environment::setObjects(const QVariantList& objects)
{
    if(objects == mObjects)
        return;

    mObjects = objects;
    emit objectsChanged(mObjects);
}

inline bool segmentsIntersection(const std::array<QVector2D,2>& s1,
                                 const std::array<QVector2D,2>& s2)
{
    auto s1Vec = (s1[1] - s1[0]).toVector3D();
    auto s2Vec = (s2[1] - s2[0]).toVector3D();

    float cp1 = QVector3D::crossProduct(s1Vec, (s2[0] - s1[0]).toVector3D()).z();
    float cp2 = QVector3D::crossProduct(s1Vec, (s2[1] - s1[0]).toVector3D()).z();

    float cp3 = QVector3D::crossProduct( s2Vec, (s1[0] - s2[0]).toVector3D()).z();
    float cp4 = QVector3D::crossProduct( s2Vec, (s1[1] - s2[0]).toVector3D()).z();

    return (cp1 * cp2 < 0) && (cp3 * cp4 < 0);

}

bool Environment::hasObstackle(const QVector2D &pos,
                               const QVector2D &direction,
                               float distance) const
{
    for(const QVariant objItem : mObjects)
    {
        const QVariantMap& item = objItem.value<QVariantMap>();
        QVector2D objPos = item.find("c")->value<QVector2D>();
        float objWidth = item.find("w")->value<float>();
        float objHeight = item.find("l")->value<float>();

        QVector2D c1 = objPos + QVector2D(objWidth/2, objHeight/2);
        QVector2D c2 = objPos + QVector2D(objWidth/2, -objHeight/2);
        QVector2D c3 = objPos + QVector2D(-objWidth/2, -objHeight/2);
        QVector2D c4 = objPos + QVector2D(-objWidth/2, objHeight/2);

        constexpr auto coef = 5.f/12.f;
        QVector2D c5 = objPos + QVector2D(objWidth*coef, objHeight*coef);
        QVector2D c6 = objPos + QVector2D(objWidth*coef, -objHeight*coef);
        QVector2D c7 = objPos + QVector2D(-objWidth*coef, -objHeight*coef);
        QVector2D c8 = objPos + QVector2D(-objWidth*coef, objHeight*coef);
//        qWarning() << c1 << c2 << c3 << c4;

        std::array<QVector2D, 2> l1 = {pos, pos + direction * distance};
        if(segmentsIntersection(l1, {c1,c2}) ||
                segmentsIntersection(l1, {c2,c3}) ||
                segmentsIntersection(l1, {c3,c4}) ||
                segmentsIntersection(l1, {c1,c4}) ||
                segmentsIntersection(l1, {c5,c6}) ||
                segmentsIntersection(l1, {c6,c7}) ||
                segmentsIntersection(l1, {c7,c8}) ||
                segmentsIntersection(l1, {c1,c8}))
            return true;
    }
    return false;
}
