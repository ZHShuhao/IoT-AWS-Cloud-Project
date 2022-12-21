<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <meta charset="utf-8">
  <title>dataDisplay</title>
  <script type="text/javascript" src="echarts.js"></script>
</head>
<body>
<%--<h1 align="center">Monitor</h1>--%>
<div id="chartmain" style="width:1500px; height: 800px;"></div>

</body>
<script type="text/javascript">
  let base = +new Date(2022, 12, 10);
  let oneDay = 24 * 3600;
  let data1 = [[base, Math.random() * 70]];
  let data2 = [[base, Math.random() * 60]];
  let data3 = [[base, Math.random() * 70]];
  let data4 = [[base, Math.random() * 60]];
  function create() {
    for (let i = 1; i < 100; i++) {
      let now = new Date((base += oneDay));
      data1.push([+now, Math.round((Math.random() - 0.5) * 10 + data1[i - 1][1])]);
      data2.push([+now, Math.round((Math.random() - 0.5) * 20 + data2[i - 1][1])]);
      data3.push([+now, Math.round((Math.random() - 0.5) * 30 + data3[i - 1][1])]);
      data4.push([+now, Math.round((Math.random() - 0.5) * 40 + data4[i - 1][1])]);
    }
  }
  //create();
  option = {
    legend: [{
      top:'5%',
      data: ['temperature1', 'humidity1']
    },{
      top: '60%',
      data: ['temperature2', 'humidity2']
    }],
    tooltip: {
      trigger: 'axis'
    },
    title: [{
      top:'1%',
      left: 'center',
      text: 'Monitor1'
    },
      {
        top: '55%',
        left: 'center',
        text: 'Monitor2'
      }],
    grid: [
      {
        bottom: '65%'
      },
      {
        top: '65%'
      }
    ],
// toolbox: [{
//   feature: {
//     dataZoom: {
//       yAxisIndex: 'none'
//     },
//     restore: {},
//     saveAsImage: {}
//   }
// },{
//   feature: {
//     dataZoom: {
//       yAxisIndex: 'none'
//     },
//     restore: {},
//     saveAsImage: {}
//   }
// }],
    xAxis: [{
      type: 'time',
      boundaryGap: false
    },{
      type: 'time',
      boundaryGap: false,
      gridIndex: 1
    }],
    yAxis: [{
      type: 'value'
    },
      {
        type: 'value',
        gridIndex: 1
      }],
    dataZoom: [{
      gridIndex: 0,
      xAxisIndex: [0, 1], // 对应网格的索引
      top: '45%',
      type: 'slider',
    },{
      bottom: 10,
      type: 'slider',
    }],
    series: [
      {
        name: 'temperature1',
        type: 'line',
        smooth: true,
        symbol: 'none',
//areaStyle: {},
        data: data1
      },
      {
        name: 'humidity1',
        type: 'line',
        smooth: true,
        symbol: 'none',
        data: data2
      },
      {
        name: 'temperature2',
        type: 'line',
        smooth: true,
        symbol: 'none',
//areaStyle: {},
        data: data1,
        xAxisIndex: 1,
        yAxisIndex: 1
      },
      {
        name: 'humidity2',
        type: 'line',
        smooth: true,
        symbol: 'none',
        data: data2,
        xAxisIndex: 1,
        yAxisIndex: 1
      }
    ]
  };
  setInterval(function () {
    create();
    myChart.setOption({
      series: [
        {
          data: data1
        },
        {
          data: data2
        },
        {
          data: data3,
        },
        {
          data: data4,
        }
      ]
    });
  }, 1000);
  let myChart = echarts.init(document.getElementById('chartmain'));
  myChart.setOption(option);
</script>
</html>
<%--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--%>
1:database 存alarm？