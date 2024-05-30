from Cuenta import Cuenta


class CuentaCorriente(Cuenta):
    def __init__(self, nombre, username, password, saldo=0.0, sobregiro=500.0):
        super().__init__(nombre, username, password, saldo)
        self.__sobregiro = sobregiro

    def retirar(self, monto): # Polimorfismo
        if monto > self.mostrar_saldo() + self.__sobregiro:
            raise ValueError("Saldo insuficiente incluso con sobregiro")
        self._Cuenta__saldo -= monto  # Acceder al saldo privado de la clase base

    def to_string(self):
        return f"{self.get_nombre()},{self.get_username()},{self.get_password()},{self.mostrar_saldo()},{self.__sobregiro}"
