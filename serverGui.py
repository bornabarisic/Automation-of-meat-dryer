from PyQt5 import QtWidgets     # potreban za upravljanje grafickim elementima (button, label, ...)
import sys                      # potreban za pokretanje programa
import testdesign               # import graficko sucelje koje sam napravio u designer-u


class ServerGui(QtWidgets.QMainWindow, testdesign.Ui_MainWindow):   # Glavna klasa koja ucitava desing programa (testdesign)
    def __init__(self, parent=None):
        super(ServerGui, self).__init__(parent)
        self.setupUi(self)

        self.btnVentTemp.clicked.connect(self.send_vent_temp)
        self.btnHeatTemp.clicked.connect(self.send_heat_temp)
        self.btnLight.clicked.connect(self.send_light_state)

        #inicijlaizacija vrijednosti postavki
        self.ventTemp = 25
        self.spinVentTemp.setValue(self.ventTemp)
        self.heatTemp = 18
        self.spinHeatTemp.setValue(self.heatTemp)
        self.lightState = False

    def send_vent_temp(self):
        self.ventTemp = self.spinVentTemp.value

    def send_heat_temp(self):
        self.heatTemp = self.spinHeatTemp.value

    def send_light_state(self):
        if self.lightState:
            self.btnLight.setText("Isključi")
        else:
            self.btnLight.setText("Uključi")

    def get_sensor_data(self):
        self.lblSensor.setText("Data")


def main():                                          # funkcija koja pokrece graficko sucelje sa kojim dalje raspolazem
    app = QtWidgets.QApplication(sys.argv)
    form = ServerGui()
    form.show()
    app.exec_()


if __name__ == '__main__':   # kada se pokrene program Server.py prepoznaje koju funkciju prvu pokrenuti (MAIN funkciju)
    main()


