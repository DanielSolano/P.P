from Banco import Banco
import os

def menu_usuario(banco, cuenta):
    while True:
        os.system('cls')
        print("\n--- Menu ---")   
        print("1. Mostrar saldo")
        print("2. Depositar dinero")
        print("3. Retirar dinero")
        print("4. Transferir dinero")
        print("5. Salir")
        opcion = input("Seleccione una opción: ")

        if opcion == '1':
            os.system('cls')
            print(f"Saldo actual: {cuenta.mostrar_saldo()}")
            os.system('pause')

        elif opcion == '2':
            os.system('cls')
            monto = float(input("Ingrese el monto a depositar: "))
            cuenta.depositar(monto)
            print(f"Nuevo saldo: {cuenta.mostrar_saldo()}")
            os.system('pause')
        elif opcion == '3':
            os.system('cls')
            monto = float(input("Ingrese el monto a retirar: "))
            try:
                cuenta.retirar(monto)
                print(f"Nuevo saldo: {cuenta.mostrar_saldo()}")
            except ValueError as e:
                print(e)
            os.system('pause')
        elif opcion == '4':
            os.system('cls')
            username_destino = input("Ingrese el nombre de usuario destino: ")
            monto = float(input("Ingrese el monto a transferir: "))
            try:
                banco.transferir_dinero(cuenta, username_destino, monto)
                print(f"Transferencia realizada. Nuevo saldo: {cuenta.mostrar_saldo()}")
            except ValueError as e:
                print(e)
            os.system('pause')
        elif opcion == '5':
            os.system('cls')
            print("Sesión cerrada")
            break

        else:
            os.system('cls')
            print("Opción no valida")
            os.system('pause')

banco = Banco('Practica2//usuarios.txt')

while True:
    os.system('cls')
    print("\n--- Bienvenido al banco ---")
    print("1. Registrarse")
    print("2. Iniciar sesion")
    print("3. Salir")
    opcion = input("Seleccione una opcion: ")

    if opcion == '1':
        os.system('cls')
        nombre = input("Ingrese su nombre: ")
        username = input("Ingrese un nombre de usuario: ")
        password = input("Ingrese una contraseña: ")
        tipo_cuenta = input("Ingrese el tipo de cuenta (ahorros/corriente): ").lower()
        try:
            banco.registrar_usuario(tipo_cuenta, nombre, username, password)
            print("Usuario registrado exitosamente")
        except ValueError as e:
            print(e)
        os.system('pause')

    elif opcion == '2':
        os.system('cls')
        username = input("Ingrese su nombre de usuario: ")
        password = input("Ingrese su contraseña: ")
        try:
            cuenta = banco.iniciar_sesion(username, password)
            print(f"Bienvenido, {cuenta.get_nombre()}")
            menu_usuario(banco, cuenta)
        except ValueError as e:
            print(e)
        os.system('pause')

    elif opcion == '3':
        os.system('cls')
        print("Tenga un buen día")
        os.system('pause')
        break

    else:
        os.system('cls')
        print("Opcion no válida")
        os.system('pause')
        