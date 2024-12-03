# Proyecto Patricia Tree con Crow

Este proyecto implementa un **Patricia Tree** en C++ y utiliza **Crow** como framework para crear un servidor web ligero. El proyecto permite insertar claves en el árbol y visualizar su estructura mediante **Graphviz**.

---

## **Requisitos previos**
Antes de comenzar, asegúrate de tener instalados los siguientes componentes en tu sistema:

- **Git**: Para clonar el repositorio de Crow.
- **Boost**: Biblioteca necesaria para Crow.
- **Graphviz**: Para generar visualizaciones del árbol Patricia.
- **G++**: Compilador compatible con C++17.

---

## **Pasos de configuración**

### **1. Configurar Crow**
1. Clona el repositorio oficial de Crow:
   ```bash
   git clone https://github.com/CrowCpp/Crow.git
   ```
2. Navega al directorio donde se encuentra el archivo `crow.h`:
   ```bash
   cd /home/tu-username/Crow/include
   ```
3. Cambia el nombre del archivo `crow.h` a `crow_all.h` y muévelo a tu proyecto:
   ```bash
   mv /home/tu-username/Crow/include/crow.h /home/tu-username/aedPatricia/crow_all.h
   ```

---

### **2. Instalar Boost**
Crow requiere Boost para funcionar. Instálalo ejecutando:
```bash
sudo apt install libboost-all-dev
```

---

### **3. Instalar Graphviz**
Graphviz se utiliza para generar gráficos del Patricia Tree. Instálalo con el siguiente comando:
```bash
sudo apt install graphviz
```

---

### **4. Compilar el proyecto**
1. Asegúrate de que la estructura de tu proyecto sea la siguiente:
   ```
   ProjectFolder/
   ├── main.cpp
   ├── patricia_tree.h
   ├── patricia_tree.cpp
   ├── crow_all.h
   ```

2. Usa el siguiente comando para compilar el proyecto:
   ```bash
   g++ main.cpp patricia_tree.cpp -o server -std=c++17 -I. -lboost_system -lboost_thread -pthread
   ```

---

## **Ejecutar el servidor**
1. Una vez compilado, ejecuta el servidor con:
   ```bash
   ./server
   ```
2. Abre tu navegador web y accede a las siguientes rutas para interactuar con el servidor:
   - **Insertar una clave en el Patricia Tree**:
     - Método: `POST`
     - URL: `http://localhost:8080/insert`
     - Cuerpo de la solicitud (JSON):
       ```json
       {
           "key": "tu-clave-a-insertar"
       }
       ```
   - **Visualizar el árbol Patricia**:
     - URL: `http://localhost:8080/tree`
     - Descargará una imagen PNG del árbol generado.

---

## **Generar manualmente el gráfico del Patricia Tree**
1. Después de ejecutar el servidor, se generará un archivo `patricia_tree.dot`.
2. Usa Graphviz para convertirlo a un archivo PNG:
   ```bash
   dot -Tpng patricia_tree.dot -o patricia_tree.png
   ```
3. Abre el archivo `patricia_tree.png` para visualizar el árbol.

---

## **Contribuciones**
Si deseas mejorar este proyecto o encontrar un problema, ¡envía un pull request o abre un issue en el repositorio!