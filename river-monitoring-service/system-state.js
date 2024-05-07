const Period = {
    P1: 1000,
    P2: 500
}

const SystemState = {
    Normal: {
        name: "NORMAL",
        samplePeriod: Period.P1,
        Badge: {
            name: "Normal",
            icon: `<i class="bi bi-check-lg fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>`,
            style: "border-success text-success",
            styleHex: "#198754"
        }
    },
    AlarmTooLow: {
        name: "ALARM-TOO-LOW",
        samplePeriod: Period.P1,
        Badge: {
            name: "Low",
            icon: `<i class="bi bi-chevron-down fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>`,
            style: "border-warning text-warning",
            styleHex: "#ffc107"
        }
    },
    PreAlarmTooHigh: {
        name: "PRE-ALARM-TOO-HIGH",
        samplePeriod: Period.P2,
        Badge: {
            name: "High",
            icon: `<i class="bi bi-dash-lg fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>`,
            style: "border-warning text-warning",
            styleHex: "#ffc107"
        }
    },
    AlarmTooHigh: {
        name: "ALARM-TOO-HIGH",
        samplePeriod: Period.P2,
        Badge: {
            name: "High",
            icon: `<i class="bi bi-chevron-up fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>`,
            style: "border-warning text-warning",
            styleHex: "#ffc107"
        }
    },
    AlarmTooHighCritic: {
        name: "ALARM-TOO-HIGH-CRITIC",
        samplePeriod: Period.P2,
        Badge: {
            name: "High",
            icon: `<i class="bi bi-chevron-double-up fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>`,
            style: "border-danger text-danger",
            styleHex: "#dc3545"
        }
    }
}

module.exports = SystemState
