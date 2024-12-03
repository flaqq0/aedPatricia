#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <cstdlib>
#include "crow_all.h"

#include "patricia_tree.h" // Código del Patricia Tree

class MainWindow : public QWidget {
    Q_OBJECT
private:
    PatriciaTree tree;
    QLineEdit* keyInput;
    QLabel* imageLabel;

public:
    MainWindow(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        keyInput = new QLineEdit(this);
        keyInput->setPlaceholderText("Enter key to insert");

        QPushButton* insertButton = new QPushButton("Insert Key", this);
        connect(insertButton, &QPushButton::clicked, this, &MainWindow::insertKey);

        imageLabel = new QLabel(this);

        layout->addWidget(keyInput);
        layout->addWidget(insertButton);
        layout->addWidget(imageLabel);

        setLayout(layout);
    }

private slots:
    void insertKey() {
        QString key = keyInput->text();
        if (!key.isEmpty()) {
            tree.insert(key.toStdString());
            tree.exportToGraphviz("patricia_tree.dot");
            system("dot -Tpng patricia_tree.dot -o patricia_tree.png");
            imageLabel->setPixmap(QPixmap("patricia_tree.png"));
        }
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Patricia Tree Viewer");
    window.show();
    return app.exec();
}
