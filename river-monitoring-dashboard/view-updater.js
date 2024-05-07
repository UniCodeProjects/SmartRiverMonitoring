const ControlMode = {
    Automatic: 'Automatic',
    Manual: 'Manual'
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
        // Showing range tooltip.
        const tooltip = new bootstrap.Tooltip(document.getElementById('valve-range'), { trigger: 'manual' });
        tooltip.show();
        setTimeout(_ => tooltip.hide(), 4000);
    } else {
        setControlMode(ControlMode.Automatic);
    }
}

function updateProgressBar(value) {
    const progressBar = document.getElementById('valve-bar');
    const valuePercentage = value + '%';
    progressBar.style.width = valuePercentage;
    progressBar.innerHTML = valuePercentage;
    progressBar.setAttribute('aria-valuenow', value);
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
    $('#valve-range').val(value);
    toggleValveOpeningInput(false);
}
