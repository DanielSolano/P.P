from Cuenta import Cuenta

# Herencia
class CuentaAhorros(Cuenta):
    def __init__(self, nombre, username, password, saldo=0.0):
        super().__init__(nombre, username, password, saldo)

    def retirar(self, monto): # Polimorfismo
        if monto > self.mostrar_saldo() * 0.8:
            raise ValueError("No puede retirar mas del 80% de su saldo en una cuenta de ahorros")
        super().retirar(monto)