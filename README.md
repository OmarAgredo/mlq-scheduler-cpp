# MLQ Scheduler en C++

Simulador de planificacion de procesos con MLQ (Multilevel Queue Scheduling),
desarrollado en C++ con programacion orientada a objetos para un parcial de
Sistemas Operativos.

## Video explicativo

[Ver video en YouTube](https://youtu.be/vmYNM-N4Sko)

## Autor

Omar Esteban Agredo

## Algoritmo implementado

El sistema usa tres colas con prioridad fija:

- Queue 1: Round Robin con quantum 2.
- Queue 2: Round Robin con quantum 3.
- Queue 3: STCF (Shortest Time to Completion First).

La prioridad entre colas es fija: primero se ejecutan todos los procesos de la
cola 1, despues los de la cola 2 y finalmente los de la cola 3.

El `currentTime` es global y se conserva entre colas. Cada algoritmo respeta el
`arrivalTime`; si no hay procesos disponibles, el tiempo avanza hasta la
siguiente llegada.

## Estructura del proyecto

```text
mlq-scheduler-cpp/
  README.md
  .gitignore
  inputs/
    mlq003.txt
    mlq006.txt
    mlq007.txt
    mlq_custom.txt
  outputs/
  src/
    main.cpp
    model/
      Process.h
      Process.cpp
    scheduler/
      Scheduler.h
      RoundRobinScheduler.h
      RoundRobinScheduler.cpp
      STCFScheduler.h
      STCFScheduler.cpp
      MLQScheduler.h
      MLQScheduler.cpp
    io/
      ProcessFileReader.h
      ProcessFileReader.cpp
      ResultFileWriter.h
      ResultFileWriter.cpp
    util/
      MetricsCalculator.h
      MetricsCalculator.cpp
```

## Compilacion

```bash
g++ src/main.cpp src/model/Process.cpp src/scheduler/RoundRobinScheduler.cpp src/scheduler/STCFScheduler.cpp src/scheduler/MLQScheduler.cpp src/io/ProcessFileReader.cpp src/io/ResultFileWriter.cpp src/util/MetricsCalculator.cpp -o mlq_scheduler
```

## Ejecucion

En Windows:

```bash
.\mlq_scheduler.exe inputs/mlq_custom.txt outputs/mlq_custom_output.txt
```

En Linux/Mac:

```bash
./mlq_scheduler inputs/mlq_custom.txt outputs/mlq_custom_output.txt
```

Sin argumentos, el programa ejecuta por defecto los archivos definidos en
`main.cpp` y genera sus respectivos archivos de salida en `outputs/`.

## Formato de entrada

Cada linea valida tiene cinco campos separados por punto y coma:

```text
etiqueta; burstTime; arrivalTime; queue; priority
```

Ejemplo:

```text
A;4;0;1;5
B;3;1;1;4
C;5;0;2;3
D;2;4;2;2
E;6;2;3;1
```

Las lineas vacias y las que empiezan con `#` se ignoran.

## Formato de salida

El archivo de salida contiene una linea por proceso con sus datos y metricas:

```text
# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT
A;4;0;1;5;2;6;0;6
B;3;1;1;4;3;7;1;6
```

Al final se incluyen los promedios generales:

```text
# WT=6.40; CT=11.80; RT=5.20; TAT=10.40;
```

## Metricas

- CT (Completion Time): tiempo en que termina el proceso.
- TAT (Turnaround Time): `CT - AT`.
- WT (Waiting Time): `TAT - BT`.
- RT (Response Time): `firstStartTime - AT`.

## Caso de prueba propio

El archivo `inputs/mlq_custom.txt` contiene un caso de prueba creado para validar
el comportamiento de las tres colas:

```text
A;4;0;1;5
B;3;1;1;4
C;5;0;2;3
D;2;4;2;2
E;6;2;3;1
```

En este caso, A y B pertenecen a la cola 1, C y D a la cola 2, y E a la cola 3.
Esto permite observar como la prioridad fija entre colas afecta los tiempos de
espera y respuesta.
