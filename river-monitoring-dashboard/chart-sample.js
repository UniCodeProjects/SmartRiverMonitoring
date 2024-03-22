const ctx = document.getElementById('myChart');
  
    new Chart(ctx, {
      type: 'line',
      data: {
        labels: [0, 10, 20, 30, 40, 50, 60],
        datasets: [{
          label: 'Water level',
          data: [50, 30, 60, 5, 70, 75, 80],
          borderWidth: 1
        }]
      },
      options: {
        scales: {
          x: {
            type: 'linear',
            title: {
              display: true,
              text: 'Time (seconds)'
            }
          },
          y: {
            title: {
              display: true,
              text: 'Water Level (meters)'
            }
          }
        }
      }
    });
