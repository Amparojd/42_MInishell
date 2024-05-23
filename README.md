<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <img src="./img/anshellmogif.gif">
    <h3 text align= "center">Proyecto de 42 Madrid</h3>
    <li>
        <h3>Introducción</h3>
        <h3>Instalación</h3>
        <h3>Diagramas y apuntes</h3>
        <img src="./img/comandos.drawio.png">
    </li>
    <br>
    <h2>Variables de entorno</h2>
    <h3>VARIABLES DE ENTORNO</h3>

<p>Son variables de contienen información sobre el sistema operativo y la configuración del usuario. 
Son utilizadas por el Shell y por las aplicaciones para determinar cómo funcionan y se comportan
Se pueden definir, modificar y eliminar según las necesidades del usuario o sistema</p>

<h4>Ejemplos de variables de entorno</h4>
<h5>PATH:</h5>
<p>Especifica las ubicaciones donde el sistema buscará ejecutables cuando se ingresa un comando en la línea de comandos</p>
<pre><code>PATH=/usr/local/bin:/usr/bin:/bin</code></pre>
<h5>HOME:</h5>
<p>Indica el directorio de inicio del usuario actual</p>
<pre><code>HOME=/home/usuario</code></pre>
<h5>USER:</h5>
<p>Contiene en nombre del usuario actual</p>
<pre><code>USER=Just-Think</code></pre>
<h5>SHELL:</h5>
<p>Almacena la ruta del Shell que está utilizando el usuario actualmente</p>
<pre><code>SHELL=/bin/bash</code></pre>
<h5>PS1:</h5>
<p>Define el formato del prompt del shell</p>
<pre><code>PS1='\u@\h:\w\$ '</code></pre>
<h5>LANG:</h5>
<p>Determina la configuración regional y de idioma del usuario</p>
<pre><code>LANG=en_US.UTF-8</code></pre>
<h5>TERM:</h5>
<p>Define el tipo de terminal que el usuario está utilizando</p>
<pre><code>TERM=xterm-256color
</code></pre>
<br>
<h3>Export</h3>
<p>Comando que sirve para establecer variables de entorno en sistemas UNIX, lo que permite que estas variables sean accesibles por cualquier proceso hijo de Shell actual</p>
<p>Ejemplo:</p>
<p>Ejecutamos en Bash:<pre><code>export MY_VARIABLE=valor</code></pre>. Con esto, hemos creado una variable de entorno llamada<code>MY_VARIABLE</code> con un valor.</p>
<p>Ahora esta variable de entorno estará disponible para cualquier proceso hijo de tu Shell actual. Si luego ejecutas un script o un programa desde ese Shell, podrá acceder a <code>MY_VARIABLE</code> y su contenido</p>
<h5>Casos difíciles</h5>
<p>Vamos a jugar con dos variables que todavía no hemos creado</p>
<p><em>*Nota: Para acceder al valor de una variable debes escribir <code>echo $MY_VARIABLE</code></em></p>
<p>Si probamos a expandir <code>$a=$b</code>Nos va a dar un error, ya que a no existe y por tanto no puede acceder (expandir) ningún valor</p>
<p>Ahora vamos a crear de verdad una variable llamada "a". <pre><code>export a=abc</code></pre></p>
<p>Ahora si expandimos nos debería dar abc (su valor)<pre><code>echo $a</code></pre></p>
<p>Bien, Ahora vamos a probar a darle al valor de la variable <code>a</code> el valor de la variable <code>b</code> (b no la hemos creado)</p>
<pre><code>export $a=$b</code></pre>
<p>Intenta establecer una variable de entorno con el valor de otra variable de entorno. Sin embargo, hay un error en la sintaxis. <code>$a</code> se interpreta como el valor de la variable <code>a</code>, que es <code>abc</code>, y <code>$b</code> se interpreta como el valor de la variable <code>b</code>. Sin embargo, al no haberse definido <code>b</code>, <code>$b</code> será interpretado como una cadena vacía o nula. Por lo tanto, este comando intenta establecer la variable de entorno <code>abc</code> con un valor vacío o nulo.</p>
<p>Vamos a solucionar eso creando una variable <code>b</code></p>
<pre><code>export b=defghijklmno</code></pre>
<p>y volvemos a intentarlo de nuevo con la variable <code>b</code> creada</p>
<pre><code>export $a=$b</code></pre>
<p>Y si hacemos esto...</p>
<pre><code>echo $abc</code></pre>
<p>¡Magia! Ahora <code>abc</code> expande el contenido de la variable <code>b</code></p>

</body>
</html>
