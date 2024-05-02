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

function addChartData(label, newData) {
  chart.data.labels.push(label);
  chart.data.datasets.forEach((dataset) => {
    dataset.data.push(newData);
  });
  chart.update();
}

function removeChartData() {
  chart.data.labels.pop();
  chart.data.datasets.forEach((dataset) => {
    dataset.data.pop();
  });
  chart.update();
}
