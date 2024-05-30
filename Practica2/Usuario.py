# Clase base para abstracción de datos y encapsulamiento
class Usuario:
    def __init__(self, nombre, username, password):
        self.__nombre = nombre
        self.__username = username
        self.__password = password

    def verificar_password(self, password):
        return self.__password == password

    def get_nombre(self):
        return self.__nombre

    def get_username(self):
        return self.__username

    def get_password(self):
        return self.__password

    def to_string(self):
        return f"{self.__nombre},{self.__username},{self.__password}"