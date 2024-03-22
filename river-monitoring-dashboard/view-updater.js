function initComponents() {
    const initialValue = 0;    // TODO: get actual value.
    updateProgressBar(initialValue);
    setRangeValue(initialValue);
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
