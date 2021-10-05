#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);
	QQuickView view;
	auto engine = view.engine();
	if(!engine)
		return -1;
	engine->addImportPath(QCoreApplication::applicationDirPath() + "/qmlmodules/");
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl(argv[1]));
	view.show();

	return app.exec();
}
