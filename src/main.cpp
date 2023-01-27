// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml>
#include <QQuickWindow>
#include <QQuickStyle>

#include <KAboutData>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <KDBusService>

constexpr auto APPLICATION_ID = "org.kde.vail";

#include "version-vail.h"
#include "config.h"
#include "controller.h"

#ifdef Q_OS_ANDROID
Q_DECL_EXPORT
#endif
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

#ifdef Q_OS_ANDROID
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle(QStringLiteral("org.kde.breeze"));
#else
    QApplication app(argc, argv);
    // Default to org.kde.desktop style unless the user forces another style
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }
#endif

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    QApplication::setStyle(QStringLiteral("breeze"));
    auto font = app.font();
    font.setPointSize(10);
    app.setFont(font);
#endif

    KLocalizedString::setApplicationDomain("vail");

    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));

    KAboutData aboutData(QStringLiteral("vail"),
                         i18nc("@title", "Vail"),
                         QStringLiteral(VAIL_VERSION_STRING),
                         i18n("Communicate using Morse"),
                         KAboutLicense::GPL,
                         i18n("© 2022"));
    aboutData.addAuthor(i18nc("@info:credit", "Felipe Kinoshita"), i18nc("@info:credit", "Author"), QStringLiteral("kinofhek@gmail.com"), QStringLiteral("https://fhek.gitlab.io"));
    aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"), i18nc("EMAIL OF TRANSLATORS", "Your emails"));
    aboutData.setBugAddress("https://invent.kde.org/fhek/vail/-/issues/new");
    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.kde.vail")));

    QQmlApplicationEngine engine;

    auto config = Config::self();
    qmlRegisterSingletonInstance(APPLICATION_ID, 1, 0, "Config", config);

    qmlRegisterSingletonType(APPLICATION_ID, 1, 0, "About", [](QQmlEngine *engine, QJSEngine *) -> QJSValue {
        return engine->toScriptValue(KAboutData::applicationData());
    });

    Controller controller;
    qmlRegisterSingletonInstance(APPLICATION_ID, 1, 0, "Controller", &controller);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    KDBusService service(KDBusService::Unique);

    // Restore window size and position
    const auto rootObjects = engine.rootObjects();
    for (auto obj : rootObjects) {
        auto view = qobject_cast<QQuickWindow *>(obj);
        if (view) {
            if (view->isVisible()) {
                controller.restoreWindowGeometry(view);
            }
            break;
        }
    }

    return app.exec();
}
