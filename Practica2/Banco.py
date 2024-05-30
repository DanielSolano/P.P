from Cuenta import Cuenta
from Cuenta_ahorro import CuentaAhorros
from Cuenta_corriente import CuentaCorriente
import os

# Clase que maneja la gestión del banco
class Banco:
    def __init__(self, nombre_archivo):
        self.nombre_archivo = nombre_archivo
        self.usuarios = self._cargar_datos()

    def _cargar_datos(self):
        usuarios = {}
        if os.path.exists(self.nombre_archivo):
            with open(self.nombre_archivo, 'r') as file:
                for linea in file:
                    datos = linea.strip().split(',')
                    if len(datos) == 4:
                        nombre, username, password, saldo = datos
                        usuarios[username] = Cuenta(nombre, username, password, float(saldo))
                    elif len(datos) == 5:
                        nombre, username, password, saldo, sobregiro = datos
                        usuarios[username] = CuentaCorriente(nombre, username, password, float(saldo), float(sobregiro))
        return usuarios

    def _guardar_datos(self):
        with open(self.nombre_archivo, 'w') as file:
            for cuenta in self.usuarios.values():
                file.write(cuenta.to_string() + '\n')

    def registrar_usuario(self, tipo_cuenta, nombre, username, password):
        if username in self.usuarios:
            raise ValueError("El usuario ya existe")
        if tipo_cuenta == "ahorros":
            cuenta = CuentaAhorros(nombre, username, password)
        elif tipo_cuenta == "corriente":
            cuenta = CuentaCorriente(nombre, username, password)
        else:
            cuenta = Cuenta(nombre, username, password)
        self.usuarios[username] = cuenta
        self._guardar_datos()

    def iniciar_sesion(self, username, password):
        if username in self.usuarios:
            cuenta = self.usuarios[username]
            if cuenta.verificar_password(password):
                return cuenta
        raise ValueError("Usuario o contraseña incorrecta")

    def transferir_dinero(self, cuenta_origen, username_destino, monto):
        if username_destino in self.usuarios:
            cuenta_destino = self.usuarios[username_destino]
            if monto > cuenta_origen.mostrar_saldo():
                raise ValueError("Saldo insuficiente para la transferencia")
            cuenta_origen.retirar(monto)
            cuenta_destino.depositar(monto)
            self._guardar_datos()
        else:
            raise ValueError("El usuario destino no existe")