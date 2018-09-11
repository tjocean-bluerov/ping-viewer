#pragma once

#include <QLoggingCategory>
#include <QSettings>
#include <QStringListModel>

#include "qjsonsettings.h"
#include "settingsmanagerhelper.h"

class QJSEngine;
class QQmlEngine;

Q_DECLARE_LOGGING_CATEGORY(SETTINGSMANAGER)

/**
 * @brief Manage the project SettingsManager
 *
 */
class SettingsManager : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Get variable value
     *
     * @param settingName
     * @return QVariant
     */
    Q_INVOKABLE QVariant value(QString& settingName);

    /**
     * @brief Set variable value
     *
     * @param settingName
     * @param value
     */
    Q_INVOKABLE void set(QString& settingName, QVariant& value);

    /**
     * @brief Return QSettings reference
     *
     * @return QSettings&
     */
    QSettings& settings() { return _settings; };

    /**
     * @brief Return SettingsManager pointer
     *
     * @return SettingsManager*
     */
    static SettingsManager* self();
    ~SettingsManager();

    /**
     * @brief Return a pointer of this singleton to the qml register function
     *
     * @param engine
     * @param scriptEngine
     * @return QObject*
     */
    static QObject* qmlSingletonRegister(QQmlEngine* engine, QJSEngine* scriptEngine);

private:
    SettingsManager* operator = (SettingsManager& other) = delete;
    SettingsManager(const SettingsManager& other) = delete;
    SettingsManager();

    QSettings _settings;

    /**
     * @brief This will create all gets, sets, signals and private variables,
     */

    // Everything after this line should be AUTO_PROPERTY
    AUTO_PROPERTY(bool, debugMode)
    AUTO_PROPERTY(bool, replayMenu)
    AUTO_PROPERTY(bool, reset)
    AUTO_PROPERTY(bool, logSCrollLock)
    //AUTO_PROPERTY_MODEL(QString, adistanceUnits, QStringList, MODEL({"Metric", "Imperial"})) // Example
    AUTO_PROPERTY_JSONMODEL(distanceUnits, QByteArrayLiteral(R"({
            "settings": [
                {
                    "name": "Metric",
                    "distance": "m",
                    "distanceScalar": 1
                },
                {
                    "name": "Imperial",
                    "distance": "ft",
                    "distanceScalar": 3.280839895
                }
            ]
        })"))

};