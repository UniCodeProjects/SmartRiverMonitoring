const SystemState = {
    Normal: 'NORMAL',
    AlarmTooLow: 'ALARM-TOO-LOW',
    PreAlarmTooHigh: "PRE-ALARM-TOO-HIGH",
    AlarmTooHigh: 'ALARM-TOO-HIGH',
    AlarmTooHighCritic: 'ALARM-TOO-HIGH-CRITIC'
}

const ControlMode = {
    Automatic: 'Automatic',
    Manual: 'Manual'
}

function initComponents() {
    const initialValue = 0;    // TODO: get actual value.
    updateProgressBar(initialValue);
    setRangeValue(initialValue);
    // updateStatusBadge(SystemState.Normal);   // TODO: use actual value.
    setControlMode();
}

function setControlMode(mode = ControlMode.Automatic) {
    switch (mode) {
        case ControlMode.Automatic:
            document.getElementById('valve-range').disabled = true;
            document.getElementById('manual-mode-switch').checked = false;
            break;
        case ControlMode.Manual:
            document.getElementById('valve-range').disabled = false;
            document.getElementById('manual-mode-switch').checked = true;
            break;
        default:
            console.error("Unknown control mode: ", mode);
            break;
    }
}

function toggleManualMode() {
    const isManual = document.getElementById('manual-mode-switch').checked;
    if (isManual) {
        setControlMode(ControlMode.Manual);
    } else {
        setControlMode(ControlMode.Automatic);
    }
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

function toggleValveOpeningInput(show = true) {
    const numberInput = document.getElementById('valve-opening-input');
    numberInput.value = document.getElementById('valve-range').value;
    const modalElement = document.getElementById('valve-value-modal');
    if (show) {
        const modal = bootstrap.Modal.getInstance(modalElement);
        // If there is no instance of the modal, create a new one.
        if (modal == null) {
            new bootstrap.Modal(modalElement).show();
        } else {
            modal.show();
        }
    } else {
        const modal = bootstrap.Modal.getInstance(modalElement);
        modal.hide();
    }
}

function saveModalChanges(value) {
    var valveOpeningInput = document.getElementById('valve-opening-input');
    if (!valveOpeningInput.checkValidity()) {
        toggleValveOpeningInput(false);
        new bootstrap.Toast(document.getElementById('invalid-input-toast')).show();
        return;   
    }
    updateProgressBar(value);
    setRangeValue(value);
    toggleValveOpeningInput(false);
}
