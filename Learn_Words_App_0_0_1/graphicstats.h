#ifndef GRAPHICSTATS_H
#define GRAPHICSTATS_H

#include <QWidget>

namespace Ui {
class GraphicStats;
}

class GraphicStats : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicStats(QWidget *parent = nullptr);
    ~GraphicStats();

private:
    Ui::GraphicStats *ui;
};

#endif // GRAPHICSTATS_H
