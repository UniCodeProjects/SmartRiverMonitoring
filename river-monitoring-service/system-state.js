const Period = {
    P1: 1000,
    P2: 500
}

const SystemState = {
    Normal: {
        name: "NORMAL",
        samplePeriod: Period.P1
    },
    AlarmTooLow: {
        name: "ALARM-TOO-LOW",
        samplePeriod: Period.P1
    },
    PreAlarmTooHigh: {
        name: "PRE-ALARM-TOO-HIGH",
        samplePeriod: Period.P2
    },
    AlarmTooHigh: {
        name: "ALARM-TOO-HIGH",
        samplePeriod: Period.P2
    },
    AlarmTooHighCritic: {
        name: "ALARM-TOO-HIGH-CRITIC",
        samplePeriod: Period.P2
    }
}

module.exports = SystemState
