# Reporte Git y Github

Clase: Paradigmas de Programación

### Crear / Verificar cuenta de Github

- Abre tu navegador web y ve a [Github.com](https://github.com/).
- Haz clic en "Sign up" si no tienes una cuenta. Si ya tienes una, inicia sesión.

### Instalar / Verificar Git

- Verifica la instalación ejecutando `git --version` en tu terminal.
- Si no tienes Git instalado, descárgalo e instálalo desde [git-scm.com](https://git-scm.com/).

### Crear carpeta del proyecto

- Elige el lugar donde deseas almacenar tu proyecto en tu sistema de archivos.
- Crea una nueva carpeta para tu proyecto si aún no tienes una.
- En la terminal, en este caso bash, ejecuta los siguientes comandos (ejemplo):

```bash
$mkdir paradigmas/practica0   // Crear carpetas
$cd paradigmas/practica0      // Cambiar directorio
$touch prueba.md              // Crear archivo
$nano prueba.md               // Abrir archivo en editor de texto
$cat prueba.md                // Leer archivo en terminal
$rm prueba.md                 // Eliminar archivo
$code README.md               // Abrir archivo en VSCode
```

### Inicializar repositorio

- Abre tu terminal o símbolo del sistema.
- Navega hasta la carpeta de tu proyecto usando el comando `cd`.
- Ejecuta `git init` para inicializar un nuevo repositorio Git en la carpeta.

```bash
$cd ..                           // Volver al directorio anterior
$git init                        // Inicializar repositorio local de git
$git status                      // Verificar el estado de los archivos en el repositorio
$git add README.md               // Añadir archivo a los archivos rastreados
$git commit -m "primer commit"   // Crear un commit con los cambios actuales
```

### Crear llave pública / privada

- Si aún no tienes una llave SSH, genera una usando el comando `ssh-keygen`.
- Localiza el archivo creado y léelo usando el comando `cat`.

```bash
$ssh-keygen
$ls ~/.ssh
$cat ~/.ssh/id_rsa.pub
```

### Crear repositorio en Github

- Inicia sesión en tu cuenta de Github.
- Haz clic en el signo más en la esquina superior derecha y selecciona "New repository".
- Nombra tu repositorio, establece la visibilidad y otras configuraciones según tu preferencia.
- Haz clic en "Create repository".

### Agregar llave a Github

- Copia el contenido de tu llave pública creada anteriormente.
- Ve a la configuración de tu cuenta de Github haciendo clic en tu avatar en la esquina superior derecha y selecciona "Settings".
- En el menú de la izquierda, haz clic en "SSH and GPG keys".
- Haz clic en "New SSH key".
- Pega el contenido de tu llave pública en el campo "Key" y dale un nombre descriptivo.
- Haz clic en "Add SSH key" para guardar.

### Clonar repositorio

- Ve a Github y haz clic en "Code", luego copia el código de SSH.
- En tu terminal, navega hasta la carpeta donde deseas clonar el repositorio.
- Ejecuta `git clone` seguido del código de SSH que copiaste.

```bash
$mkdir temp
$cd temp
$git clone git@github.com:Scalaptia/paradigmas-de-programacion.git
$cd paradigmas-de-programacion
```

### Crear branch

- Crea un nuevo branch usando el comando `git checkout -b` seguido del nombre del branch.
- Verifica que estás en el branch correcto usando `git status`.

```bash
$git checkout -b temp          // Crear branch
$git status                    // Verificar branch
```

- Realiza cambios en tu proyecto y haz un commit.

```bash
$code .                                    // Abrir proyecto en VSCode
$git add Practicas/Practica00/README.md    // Añadir archivo a los archivos rastreados
$git commit -m "Modificar README"          // Crear commit con los cambios
```

- Sube tu branch a Github usando el comando `git push` seguido de `-u origin` y el nombre del branch. (-u origin solo se usa la primera vez, después solo se usa git push)

```bash
$git push -u origin temp   // Subir branch a Github
```

### Restaurar cambios

- Haz un cambio pero no lo añadas al stage.
- Usa el comando `git restore` seguido de un punto para eliminar los cambios.

```bash
$git restore .  // Eliminar cambios
```

- Si añadiste el cambio, ejecuta lo siguiente:

```bash
$git restore --staged Practicas/Practica00/README.md
```

### Fusionar branch

- Cambia al branch que deseas fusionar.
- Ejecuta `git merge` seguido del nombre del branch que deseas fusionar.

```bash
$git checkout main
$git merge temp
```