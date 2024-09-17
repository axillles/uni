#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QSlider>
#include <QLabel>
#include <QFrame>
#include <QColor>
#include <QLineEdit>
#include <QFormLayout>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>

class ColorConverterApp : public QWidget {
    Q_OBJECT

public:
    ColorConverterApp(QWidget *parent = nullptr);

private slots:
    void chooseColor();
    void updateColor();
    void convertColor();
    void updateFromHex();
    void updateFromHsv();
    void updateFromXyz();

private:
    QColor currentColor;
    QSlider *rSlider, *gSlider, *bSlider;
    QSlider *hSlider, *sSlider, *vSlider;
    QSlider *xSlider, *ySlider, *zSlider;
    QLineEdit *hexEntry;
    QFrame *colorDisplay;
    QLabel *rLabel, *gLabel, *bLabel;
    QLabel *hLabel, *sLabel, *vLabel;
    QLabel *xLabel, *yLabel, *zLabel;

    void updateColorDisplay();
    void rgbToXyz(int r, int g, int b, float &X, float &Y, float &Z);
    void rgbToHsv(int r, int g, int b, int &H, int &S, int &V);
    void hsvToRgb(int H, int S, int V, int &r, int &g, int &b);
    void xyzToRgb(float X, float Y, float Z, int &r, int &g, int &b);
};

ColorConverterApp::ColorConverterApp(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);     // layout

    // RGB Sliders
    QHBoxLayout *rgbLayout = new QHBoxLayout;
    rSlider = new QSlider(Qt::Horizontal);
    gSlider = new QSlider(Qt::Horizontal);
    bSlider = new QSlider(Qt::Horizontal);
    rLabel = new QLabel("0");
    gLabel = new QLabel("0");
    bLabel = new QLabel("0");

    rSlider->setRange(0, 255);
    gSlider->setRange(0, 255);
    bSlider->setRange(0, 255);

    rgbLayout->addWidget(new QLabel("R:"));
    rgbLayout->addWidget(rSlider);
    rgbLayout->addWidget(rLabel);
    rgbLayout->addWidget(new QLabel("G:"));
    rgbLayout->addWidget(gSlider);
    rgbLayout->addWidget(gLabel);
    rgbLayout->addWidget(new QLabel("B:"));
    rgbLayout->addWidget(bSlider);
    rgbLayout->addWidget(bLabel);
    mainLayout->addLayout(rgbLayout);

    // HSV Sliders
    QHBoxLayout *hsvLayout = new QHBoxLayout;
    hSlider = new QSlider(Qt::Horizontal);
    sSlider = new QSlider(Qt::Horizontal);
    vSlider = new QSlider(Qt::Horizontal);
    hLabel = new QLabel("0");
    sLabel = new QLabel("0");
    vLabel = new QLabel("0");

    hSlider->setRange(0, 360);
    sSlider->setRange(0, 100);
    vSlider->setRange(0, 100);

    hsvLayout->addWidget(new QLabel("H:"));
    hsvLayout->addWidget(hSlider);
    hsvLayout->addWidget(hLabel);
    hsvLayout->addWidget(new QLabel("S:"));
    hsvLayout->addWidget(sSlider);
    hsvLayout->addWidget(sLabel);
    hsvLayout->addWidget(new QLabel("V:"));
    hsvLayout->addWidget(vSlider);
    hsvLayout->addWidget(vLabel);
    mainLayout->addLayout(hsvLayout);

    // XYZ Sliders
    QHBoxLayout *xyzLayout = new QHBoxLayout;
    xSlider = new QSlider(Qt::Horizontal);
    ySlider = new QSlider(Qt::Horizontal);
    zSlider = new QSlider(Qt::Horizontal);
    xLabel = new QLabel("0");
    yLabel = new QLabel("0");
    zLabel = new QLabel("0");

    xSlider->setRange(0, 100);
    ySlider->setRange(0, 100);
    zSlider->setRange(0, 100);

    xyzLayout->addWidget(new QLabel("X:"));
    xyzLayout->addWidget(xSlider);
    xyzLayout->addWidget(xLabel);
    xyzLayout->addWidget(new QLabel("Y:"));
    xyzLayout->addWidget(ySlider);
    xyzLayout->addWidget(yLabel);
    xyzLayout->addWidget(new QLabel("Z:"));
    xyzLayout->addWidget(zSlider);
    xyzLayout->addWidget(zLabel);
    mainLayout->addLayout(xyzLayout);


                    // HEX
    QFormLayout *hexLayout = new QFormLayout;
    hexEntry = new QLineEdit;
    hexEntry->setMaxLength(7);
    hexLayout->addRow("HEX:", hexEntry);
    mainLayout->addLayout(hexLayout);

    QRegularExpression hexRegExp("^#[0-9A-Fa-f]{6}$");
    hexEntry->setValidator(new QRegularExpressionValidator(hexRegExp, this));

    QPushButton *chooseColorButton = new QPushButton("Choose Color");
    connect(chooseColorButton, &QPushButton::clicked, this, &ColorConverterApp::chooseColor);
    mainLayout->addWidget(chooseColorButton);

    colorDisplay = new QFrame();
    colorDisplay->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    colorDisplay->setFixedSize(100, 100);
    colorDisplay->setStyleSheet("background-color: white");
    mainLayout->addWidget(colorDisplay);


    // connect RGB sliders
    connect(rSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateColor);
    connect(gSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateColor);
    connect(bSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateColor);

    // connect HSV sliders
    connect(hSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromHsv);
    connect(sSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromHsv);
    connect(vSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromHsv);

    // Connect XYZ sliders
    connect(xSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromXyz);
    connect(ySlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromXyz);
    connect(zSlider, &QSlider::valueChanged, this, &ColorConverterApp::updateFromXyz);

    connect(hexEntry, &QLineEdit::editingFinished, this, &ColorConverterApp::updateFromHex);

    setLayout(mainLayout);
}

void ColorConverterApp::chooseColor() {
    QColor chosenColor = QColorDialog::getColor(currentColor, this);
    if (chosenColor.isValid()) {
        currentColor = chosenColor;
        rSlider->setValue(currentColor.red());
        gSlider->setValue(currentColor.green());
        bSlider->setValue(currentColor.blue());
        updateColorDisplay();
        convertColor();
    }
}

void ColorConverterApp::updateColor() {
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();

    // Обновляем текстовые поля
    rLabel->setText(QString::number(r));
    gLabel->setText(QString::number(g));
    bLabel->setText(QString::number(b));

    currentColor.setRed(r);
    currentColor.setGreen(g);
    currentColor.setBlue(b);

    updateColorDisplay();
    convertColor();
}


void ColorConverterApp::updateFromHsv() {
    // Отключаем сигналы RGB ползунков, чтобы избежать циклических вызовов
    rSlider->blockSignals(true);
    gSlider->blockSignals(true);
    bSlider->blockSignals(true);

    int h = hSlider->value();
    int s = sSlider->value();
    int v = vSlider->value();
    int r, g, b;

    // Конвертируем HSV в RGB
    hsvToRgb(h, s, v, r, g, b);

    // Устанавливаем значения RGB ползунков
    rSlider->setValue(r);
    gSlider->setValue(g);
    bSlider->setValue(b);

    // Устанавливаем цвет в текущем цвете
    currentColor.setRgb(r, g, b);

    // Обновляем текстовые поля для HSV
    hLabel->setText(QString::number(h));
    sLabel->setText(QString::number(s));
    vLabel->setText(QString::number(v));

    // Также обновляем текстовые поля для RGB
    rLabel->setText(QString::number(r));
    gLabel->setText(QString::number(g));
    bLabel->setText(QString::number(b));

    // Обновляем отображение цвета
    updateColorDisplay();
    convertColor();

    // Включаем сигналы обратно
    rSlider->blockSignals(false);
    gSlider->blockSignals(false);
    bSlider->blockSignals(false);
}



void ColorConverterApp::updateFromXyz() {
    xSlider->blockSignals(true);
    ySlider->blockSignals(true);
    zSlider->blockSignals(true);

    float X = xSlider->value();
    float Y = ySlider->value();
    float Z = zSlider->value();
    int r, g, b;
    xyzToRgb(X, Y, Z, r, g, b);
    rSlider->setValue(r);
    gSlider->setValue(g);
    bSlider->setValue(b);

    // Обновляем текстовые поля
    xLabel->setText(QString::number(X));
    yLabel->setText(QString::number(Y));
    zLabel->setText(QString::number(Z));
    rLabel->setText(QString::number(r));
    gLabel->setText(QString::number(g));
    bLabel->setText(QString::number(b));

    currentColor.setRgb(r, g, b);
    updateColorDisplay();
    convertColor();

    xSlider->blockSignals(false);
    ySlider->blockSignals(false);
    zSlider->blockSignals(false);
}



void ColorConverterApp::convertColor() {
    int r = rSlider->value();
    int g = gSlider->value();
    int b = bSlider->value();

    // Конвертация RGB в HEX
    hexEntry->setText(QString("#%1%2%3")
                          .arg(r, 2, 16, QChar('0'))
                          .arg(g, 2, 16, QChar('0'))
                          .arg(b, 2, 16, QChar('0')).toUpper());

    // Конвертация RGB -> XYZ
    float X, Y, Z;
    rgbToXyz(r, g, b, X, Y, Z);

    qDebug() << "RGB to XYZ: X=" << X << " Y=" << Y << " Z=" << Z;

    xSlider->blockSignals(true);
    ySlider->blockSignals(true);
    zSlider->blockSignals(true);

    // Обновление ползунков X, Y, Z
    xSlider->setValue(static_cast<int>(X));
    ySlider->setValue(static_cast<int>(Y));
    zSlider->setValue(static_cast<int>(Z));

    // Обновление текстовых полей X, Y, Z
    xLabel->setText(QString::number(static_cast<int>(X)));
    yLabel->setText(QString::number(static_cast<int>(Y)));
    zLabel->setText(QString::number(static_cast<int>(Z)));

    xSlider->blockSignals(false);
    ySlider->blockSignals(false);
    zSlider->blockSignals(false);

    // Конвертация RGB -> HSV
    int H, S, V;
    rgbToHsv(r, g, b, H, S, V);

    qDebug() << "RGB to HSV: H=" << H << " S=" << S << " V=" << V;

    hSlider->blockSignals(true);
    sSlider->blockSignals(true);
    vSlider->blockSignals(true);

    // Обновление ползунков H, S, V
    hSlider->setValue(H);
    sSlider->setValue(S);
    vSlider->setValue(V);

    // Обновление текстовых полей H, S, V
    hLabel->setText(QString::number(H));
    sLabel->setText(QString::number(S));
    vLabel->setText(QString::number(V));

    hSlider->blockSignals(false);
    sSlider->blockSignals(false);
    vSlider->blockSignals(false);
}


void ColorConverterApp::updateFromHex() {
    QString hexColor = hexEntry->text();
    if (hexColor.isEmpty() || !QColor(hexColor).isValid()) {
        return;
    }
    QColor color(hexColor);

    int r = color.red();
    int g = color.green();
    int b = color.blue();

    rSlider->setValue(r);
    gSlider->setValue(g);
    bSlider->setValue(b);

    // Обновляем текстовые поля
    rLabel->setText(QString::number(r));
    gLabel->setText(QString::number(g));
    bLabel->setText(QString::number(b));

    currentColor = color;
    updateColorDisplay();
    convertColor();
}


void ColorConverterApp::updateColorDisplay() {
    QString colorStyle = QString("background-color: rgb(%1, %2, %3);")
                             .arg(currentColor.red())
                             .arg(currentColor.green())
                             .arg(currentColor.blue());
    colorDisplay->setStyleSheet(colorStyle);
}

void ColorConverterApp::rgbToXyz(int r, int g, int b, float &X, float &Y, float &Z) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    rf = (rf > 0.04045) ? pow((rf + 0.055) / 1.055, 2.4) : (rf / 12.92);
    gf = (gf > 0.04045) ? pow((gf + 0.055) / 1.055, 2.4) : (gf / 12.92);
    bf = (bf > 0.04045) ? pow((bf + 0.055) / 1.055, 2.4) : (bf / 12.92);

    X = rf * 0.4124 + gf * 0.3576 + bf * 0.1805;
    Y = rf * 0.2126 + gf * 0.7152 + bf * 0.0722;
    Z = rf * 0.0193 + gf * 0.1192 + bf * 0.9505;

    X *= 100;
    Y *= 100;
    Z *= 100;
}

void ColorConverterApp::xyzToRgb(float X, float Y, float Z, int &r, int &g, int &b) {
    float rf = X * 0.0032406 + Y * -0.0015372 + Z * -0.0002040;
    float gf = X * -0.0025962 + Y * 0.0062041 + Z * 0.0012183;
    float bf = X * 0.0000000 + Y * -0.0121980 + Z * 0.0123300;

    rf = (rf > 0.0031308) ? 1.055 * pow(rf, 1.0 / 2.4) - 0.055 : 12.92 * rf;
    gf = (gf > 0.0031308) ? 1.055 * pow(gf, 1.0 / 2.4) - 0.055 : 12.92 * gf;
    bf = (bf > 0.0031308) ? 1.055 * pow(bf, 1.0 / 2.4) - 0.055 : 12.92 * bf;

    int originalR = static_cast<int>(rf * 255);
    int originalG = static_cast<int>(gf * 255);
    int originalB = static_cast<int>(bf * 255);

    r = qBound(0, originalR, 255);
    g = qBound(0, originalG, 255);
    b = qBound(0, originalB, 255);

    if (r != originalR) qWarning() << "R value out of bounds, clipping occurred: " << originalR << " -> " << r;
    if (g != originalG) qWarning() << "G value out of bounds, clipping occurred: " << originalG << " -> " << g;
    if (b != originalB) qWarning() << "B value out of bounds, clipping occurred: " << originalB << " -> " << b;
}

void ColorConverterApp::rgbToHsv(int r, int g, int b, int &H, int &S, int &V) {
    QColor color(r, g, b);
    H = color.hue();
    S = color.saturation();
    V = color.value();
}

void ColorConverterApp::hsvToRgb(int H, int S, int V, int &r, int &g, int &b) {
    QColor color;
    color.setHsv(H, S, V);
    int originalR = color.red();
    int originalG = color.green();
    int originalB = color.blue();

    r = qBound(0, originalR, 255);
    g = qBound(0, originalG, 255);
    b = qBound(0, originalB, 255);

    if (r != originalR) qWarning() << "R value out of bounds, clipping occurred: " << originalR << " -> " << r;
    if (g != originalG) qWarning() << "G value out of bounds, clipping occurred: " << originalG << " -> " << g;
    if (b != originalB) qWarning() << "B value out of bounds, clipping occurred: " << originalB << " -> " << b;
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ColorConverterApp window;
    window.setWindowTitle("Color Converter");
    window.show();
    return app.exec();
}

#include "main.moc"
