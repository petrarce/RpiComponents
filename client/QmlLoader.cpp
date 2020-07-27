#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl(argv[1]));
    view.show();

    return app.exec();
}
