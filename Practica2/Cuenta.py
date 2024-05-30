from Usuario import Usuario

# Herencia
class Cuenta(Usuario):
    def __init__(self, nombre, username, password, saldo=0.0):
        super().__init__(nombre, username, password)
        self.__saldo = saldo # Encapsulamiento

    def depositar(self, monto):
        self.__saldo += monto

    def retirar(self, monto):
        if monto <= self.__saldo:
            self.__saldo -= monto
        else:
            raise ValueError("Saldo insuficiente")

    def mostrar_saldo(self):
        return self.__saldo

    def get_saldo(self):
        return self.__saldo

    def to_string(self):
        return f"{self.get_nombre()},{self.get_username()},{self.get_password()},{self.__saldo}"
