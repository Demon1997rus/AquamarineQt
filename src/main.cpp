#include <QApplication>
#include <QDir>
#include <QLockFile>
#include <QMessageBox>
#include <QDebug>

#include "widgets/mainwindow.h"
#include "utils/frameless.h"
#include "info/targetrepository.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QLockFile lockFile(QDir::temp().absoluteFilePath("Aquamarine.lock"));

    /* Пытаемся закрыть Lock File, если попытка безуспешна в течение 100 миллисекунд,
     * значит уже существует Lock File созданный другим процессом.
     * Следовательно, выбрасываем предупреждение и закрываем программу
     */
    if (!lockFile.tryLock(100))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(
            "Приложение уже запущено.\n"
            "Разрешено запускать только один экземпляр приложения.");
        msgBox.exec();
        return 1;
    }

    MainWindow window;
    FrameLess frame(&window);
    window.show();
    Q_UNUSED(frame)
    return app.exec();
}
