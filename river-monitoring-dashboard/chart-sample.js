const ctx = document.getElementById('myChart');  
const bootstrapStyle = getComputedStyle(document.body);

new Chart(ctx, {
  type: 'line',
  data: {
    labels: [0, 10, 20, 30, 40, 50, 60],
    datasets: [{
      label: 'Water level',
      data: [50, 30, 60, 5, 70, 75, 80],
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
