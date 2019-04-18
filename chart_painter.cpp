#include "chart_painter.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE
std::unique_ptr<QWidget> create_chart (std::vector<std::pair<double, double> > values_and_probabilities, std::string name)
{
  double average = 0;
  for (const std::pair<double, double> &value_and_case_count : values_and_probabilities)
    {
      double value = value_and_case_count.first;
      double probability = value_and_case_count.second;
      average += value * probability;
    }

  QBarSet *set0 = new QBarSet (name.c_str ());
  QStringList categories;
  QBarCategoryAxis *axis = new QBarCategoryAxis ();
  QBarSeries *series = new QBarSeries ();
  QChart *chart = new QChart ();

  for (const std::pair<double, double> &value_and_probability : values_and_probabilities)
    {
      double value = value_and_probability.first;
      double probability = value_and_probability.second;
      std::string value_label = (!fuzzycmp (round (value), value) ? std::to_string (static_cast<int> (value)) : std::to_string (value));
      char buf[100];
      std::sprintf (buf, "%.2f%%", probability * 100);
      std::string probability_label (buf);

      categories << (value_label + ", " + probability_label).c_str ();
      *set0 << value_and_probability.second;
    }

  series->append (set0);
  axis->append (categories);
  chart->addSeries (series);
  chart->createDefaultAxes ();
  chart->setAxisX (axis, series);

  chart->setTitle ((std::string ("Average = " ) + std::to_string (average)).c_str ());
  chart->setAnimationOptions (QChart::SeriesAnimations);
  chart->legend ()->setVisible (true);
  chart->legend ()->setAlignment (Qt::AlignBottom);

  std::unique_ptr<QChartView> chartView = std::make_unique<QChartView> (chart);
  chartView->setRenderHint (QPainter::Antialiasing);
  chartView->resize (800, 600);
  chartView->show ();
  return chartView;
}
