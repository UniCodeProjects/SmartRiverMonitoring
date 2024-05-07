const bootstrapStyle = getComputedStyle(document.body);

const chart = new Chart(document.getElementById('waterLevelChart'), {
    type: 'line',
    data: {
        datasets: [{
            label: 'Water level',
            borderWidth: 1,
            tension: 0.3,
            backgroundColor: bootstrapStyle.getPropertyValue('--bs-primary-emphasis'),
            borderColor: bootstrapStyle.getPropertyValue('--bs-primary-emphasis'),
        }]
    },
    options: {
        scales: {
            x: {
                type: 'linear',
                min: 0,
                ticks: {
                    stepSize: 1
                },
                title: {
                    display: true,
                    text: 'Time (seconds)',
                    color: bootstrapStyle.getPropertyValue('--bs-secondary')
                },
                grid: {
                    color: '#2b3035'
                }
            },
            y: {
                max: 4,    // Cytlon Technologies HC-SR04 sonar max sampling distance.
                min: 0,
                title: {
                    display: true,
                    text: 'Water Level (meters)',
                    color: bootstrapStyle.getPropertyValue('--bs-secondary')
                },
                grid: {
                    color: '#2b3035'
                }
            }
        },
        responsive: true,
        maintainAspectRatio: false
    }
});

const maxChartWindowSize = 16;
let currentXAxisMin = 1;
let currentLabel = 0;

function addChartData(newData) {
    if (chart.data.labels.length >= maxChartWindowSize) {
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
        chart.options.scales.x.min = currentXAxisMin;
        currentXAxisMin++;
    }
    chart.data.labels.push(currentLabel);
    chart.data.datasets[0].data.push(newData)
    chart.update();
    currentLabel++;
}
