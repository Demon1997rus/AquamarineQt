#include "controlpanel.h"

#include <QHeaderView>
#include <QScrollBar>

ControlPanel::ControlPanel(QWidget* parent) : QFrame(parent)
{
    initWidgets();
    controlPanelSettings();
    setupLayout();
    initializingConnections();
}

/*!
 * \brief ControlPanel::getDataMapWidgetMouseMove - данные текущего положения курсора на карте
 * \param x - координата x
 * \param y - координата y
 * \param distance - дистанция до центра круга м()
 * \param bearing - пеленг относительно центра круга(градусы)
 */
void ControlPanel::getDataMapWidgetMouseMove(int x, int y, double distance, double bearing)
{
    labelMapXY->setText(
        QString("Текущее положение курсора на карте: x = %1, y = %2").arg(x).arg(y));
    labelDistance->setText(QString("Дистанция до центра круга (м): %1").arg(distance));
    labelBearing->setText(QString("Пеленг относительно центра круга (градусы): %1").arg(bearing));
}

/*!
 * \brief ControlPanel::getSelectedIdFromMap - выбирает цель в таблице и отображает её по центру
 * \param id - идентификатор цели
 */
void ControlPanel::getSelectedIdFromMap(int id)
{
    int rowCount = model->rowCount(QModelIndex());
    for (int row = 0; row < rowCount; ++row)
    {
        QModelIndex index = model->index(row, 0);
        if (!index.isValid())
        {
            return;
        }
        if (index.data().toInt() == id)
        {
            tableView->clearSelection();  // Снимаем выделение со всех строк
            tableView->selectRow(row);  // Выделяем строку, соответствующую выбранной цели
            if (!tableView->visualRect(index).isValid())
            {
                // Прокрутим, чтобы расположить элемент в центре видового экрана.
                tableView->scrollTo(index, QAbstractItemView::PositionAtCenter);
                return;
            }
        }
    }
}

/*!
 * \brief ControlPanel::initWidgets - инициализация виджетов панели управления
 */
void ControlPanel::initWidgets()
{
    mainLayout = new QGridLayout(this);
    horizontalLayout = new QHBoxLayout();
    tableView = new QTableView(this);
    model = new TargetTableModel(this);
    labelMapXY = new QLabel("Текущее положение курсора на карте: x = 0, y = 0", this);
    labelDistance = new QLabel("Дистанция до центра круга (м): 0.0", this);
    labelBearing = new QLabel("Пеленг относительно центра круга (градусы): 0.0", this);
    pbImitation = new QPushButton("Имитация", this);
    pbPause = new QPushButton("Пауза", this);
    pbClose = new QPushButton("Выход", this);
    pbClearImitation = new QPushButton("Очистить", this);
}

/*!
 * \brief ControlPanel::controlPanelSettings - настройки панели управления
 */
void ControlPanel::controlPanelSettings()
{
    // Устанавливаем модель таблицы с целями представлению
    tableView->setModel(model);

    // Настройки кнопок управления
    pbPause->setEnabled(false);

    // Размер заголовков согласно содержимому
    tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    // Настройки label
    labelMapXY->setWordWrap(true);
}

/*!
 * \brief ControlPanel::setupLayout - установка слоя
 */
void ControlPanel::setupLayout()
{
    // Добавляем кнопки управления на вертикальный слой
    horizontalLayout->addWidget(pbImitation);
    horizontalLayout->addWidget(pbPause);
    horizontalLayout->addWidget(pbClearImitation);

    // Добавляем таблицу с целями на слой
    mainLayout->addWidget(tableView);

    // Добавляем отображения данных с карты
    mainLayout->addWidget(labelMapXY);
    mainLayout->addWidget(labelDistance);
    mainLayout->addWidget(labelBearing);

    // Добавляем вертикальный слой с кнопками
    mainLayout->addLayout(horizontalLayout, mainLayout->rowCount(), 0);

    // Добавляем кнопку "Выход"
    mainLayout->addWidget(pbClose);

    // Установка главного слоя
    setLayout(mainLayout);
}

/*!
 * \brief ControlPanel::initializingConnections - инициализация connect-ов
 */
void ControlPanel::initializingConnections()
{
    connect(pbImitation, &QPushButton::clicked, [this]() -> void {
        pbImitation->setEnabled(false);
        pbPause->setEnabled(true);
    });

    connect(pbPause, &QPushButton::clicked, [this]() -> void {
        pbImitation->setEnabled(true);
        pbPause->setEnabled(false);
    });

    connect(pbImitation, &QPushButton::clicked, this, &ControlPanel::startImitation);

    connect(pbPause, &QPushButton::clicked, this, &ControlPanel::stopImitation);

    connect(pbClose, &QPushButton::clicked, this, &ControlPanel::allClose);

    connect(pbClearImitation, &QPushButton::clicked, this, &ControlPanel::clearImitation);

    connect(tableView, &QTableView::clicked, [this](const QModelIndex& index) -> void {
        if (!index.isValid())
            return;
        QVariant value = model->index(index.row(), 0).data();
        if (!value.isValid())
            return;
        bool ok;
        int id = value.toInt(&ok);
        if (!ok)
            return;
        emit sendSelectedId(id);
    });
}
