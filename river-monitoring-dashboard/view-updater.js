const SystemState = {
    Normal: 'NORMAL',
    AlarmTooLow: 'ALARM-TOO-LOW',
    PreAlarmTooHigh: "PRE-ALARM-TOO-HIGH",
    AlarmTooHigh: 'ALARM-TOO-HIGH',
    AlarmTooHighCritic: 'ALARM-TOO-HIGH-CRITIC'
}

function initComponents() {
    const initialValue = 0;    // TODO: get actual value.
    updateProgressBar(initialValue);
    setRangeValue(initialValue);
    // updateStatusBadge(SystemState.Normal);   // TODO: use actual value.
}

function setRangeValue(value) {
    document.getElementById('valve-range').value = value;
}

function updateProgressBar(value) {
    const progressBar = document.getElementById('valve-bar');
    const valuePercentage = value + '%';
    progressBar.style.width = valuePercentage;
    progressBar.innerHTML = valuePercentage;
    progressBar.setAttribute('aria-valuenow', value);
}

function updateStatusBadge(state) {
    const statusBadge = document.getElementById('status-badge');
    const borderColourItem = statusBadge.classList.item(statusBadge.classList.length - 2);
    const textColourItem = statusBadge.classList.item(statusBadge.classList.length - 1);
    statusBadge.classList.remove(borderColourItem, textColourItem);
    const statusText = document.getElementById('status-text');
    switch (state) {
        case SystemState.Normal:
            statusText.innerHTML = `<i class="bi bi-check-lg fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>Normal`;
            statusBadge.classList.add('border-success', 'text-success');
            break;
        case SystemState.AlarmTooLow:
            statusText.innerHTML = `<i class="bi bi-chevron-down fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>Low`;
            statusBadge.classList.add('border-warning', 'text-warning');
            break;
        case SystemState.PreAlarmTooHigh:
            statusText.innerHTML = `<i class="bi bi-dash-lg fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>High`;
            statusBadge.classList.add('border-warning', 'text-warning');
            break;
        case SystemState.AlarmTooHigh:
            statusText.innerHTML = `<i class="bi bi-chevron-up fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>High`;
            statusBadge.classList.add('border-warning', 'text-warning');
            break;
        case SystemState.AlarmTooHighCritic:
            statusText.innerHTML = `<i class="bi bi-chevron-double-up fw-bold pe-1" style="-webkit-text-stroke: 0.5px;"></i>High`;
            statusBadge.classList.add('border-danger', 'text-danger');
            break;
        default:
            console.error("Unknown state: ", state);
            break;
    }
}
