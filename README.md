## lab3oop
# Вариант G Модель процессора (1.4)
Разработать приложение, позволяющее промоделировать выполнение на некотором процессоре
программы на низкоуровневом языке *(ассемблере)* в виде некоторой объектной модели. Программа представляет собой последовательность команд языка.

**Описатель команды** состоит из описателей
операндов и информации о типе операции (исполнение операции реализуется отдельным объектом функтором). В записи операторов языка могут использоваться регистры и идентификаторы (связанные с
адресами в памяти). *Регистр* – определяется номеров в блоке регистров; идентификатор –
последовательность латинских букв длиной не более 8 символов.  
**Описатель унарной команды** содержит следующую информацию: поле метки (может отсутствовать) и
указателя на операцию; описателя операнда. Результат выполнения операции помещается в операнд.  
**Описатель бинарной команды** содержит следующую информацию: поле метки (может отсутствовать) и
указателя на операции; два описателя операндов. Результат выполнения операции помещается в первый
операнд.  
**Описатель оператора перехода** содержит следующую информацию: идентификатор метки перехода в
памяти команд.  
**Описатель оператора объявления данных** содержит следующую информацию: поле метки –
идентификатор данных (обязательное поле), непосредственный операнд (число). При конструировании
объекта данного типа под операнд выделяется место в памяти программ.  
**Описатель оператора инициализации потока** содержит следующую информацию: поле метки (может
отсутствовать) и идентификатор метки перехода в памяти команд. Новый поток начинает исполнение с
заданной метки перехода, в то время как текущий поток продолжает своё исполнение со следующей
команды.  
**Описатель оператора окончания потока** одержит следующую информацию: поле метки (может
отсутствовать). Программа считается завершённой когда все потоки завершили своё исполнение
Процессор состоит из устройства управления, исполнительных устройств, выполняющих
определенные наборы операторов, блока регистров общего назначения, памяти программ и памяти данных.
При выполнении программы, очередная команда извлекается устройством управления из памяти
программ, назначается на свободное исполнительное устройство, после чего команда выполняется
исполнительным устройством с установкой блокировок на соответствующие операнды на время выполнения
команды. 
**Оператор перехода** устройство управления выполняет самостоятельно

*Блок регистров* характеризуется количеством регистров, поддерживает операции доступа к регистрам
по номеру и блокировки регистров. Хранение регистров осуществляется при помощи вектора.

Память данных характеризуется объемом, поддерживает операции доступа к данным по
идентификатору и блокировки на адреса в памяти, выделение памяти под впервые встретившийся
идентификатор.

Исполнительные устройства характеризуются набором и временем выполнения команд.

Память программ считается условно бесконечной, каждая команда занимает одну ячейку в памяти;
содержит регистр - счетчик команд, хранящий адрес текущей команды.

**Обеспечить также выполнение следующих операций.**  
*Для модели процессора:*
- редактирование модели процессора;
- выполнить программу.

*Для памяти программ:*
- редактирования программы;
- показать всю программу;
- выдать текущую команду;
- изменить значение регистра счетчика команд.

*Для любой команды:*
- вывести информацию о команде;
- редактирования команды.

*Для операнда:*
- Вернуть значение операнда.
- Для исполнительного устройства: 
- исполнить команду;
- установить / снять блокировку на ресурс памяти

1. Шаблонный класс — вектор.
2. Оператор реализуется только при выполнении задания «Многопоточность». Необходимо также обеспечить потокобезопасность всех
обращений к регистрам и памяти.
3. Расширяемый класс — команда. Необходимо предусмотреть возможность переопределения основных операций команды в новом классе -
наследнике (например, команда условного перехода).

### Полезные ссылки на материалы:  
[статья на habr](https://habr.com/ru/articles/430680/)  
[RISC](https://ru.wikipedia.org/wiki/RISC)  
[CISC](https://ru.wikipedia.org/wiki/CISC)  
[архитекура MIPS](https://ru.wikipedia.org/wiki/MIPS_(%D0%B0%D1%80%D1%85%D0%B8%D1%82%D0%B5%D0%BA%D1%82%D1%83%D1%80%D0%B0))
[Харис и Харис](https://is.ifmo.ru/books/2016/digital-design-and-computer-architecture-russian-translation_July16_2016.pdf)
[Пишем собственную виртуальную машину](https://habr.com/ru/articles/434138/#4)  
[Руководство по симулятору простого ассемблера для 8-битного процессора на Javascript](https://habr.com/ru/companies/otus/articles/680920/)

### Чужие проекты:  
https://github.com/i1i1/bbmips  
https://github.com/alexskp/MIPS-Core  
https://github.com/phrolow/Compiler  
https://github.com/phrolow/SoftCPU
https://github.com/Vladislave0-0/Processor

**[Статейка и гитхаб к ней](https://averrin.medium.com/toy-vm-c72e9d962451)**  
**https://github.com/averrin/vvm**

## Устройство процессора
![image](https://github.com/urtoach/lab3oop/assets/115491314/1711bb1b-8b98-4126-bbfb-7e73beedd10d)
![image](https://github.com/urtoach/lab3oop/assets/115491314/eb59bb8a-ba62-449c-bf03-9f0b1324a800)

[Статейка про асм для c/c++](https://cpp-kt.github.io/cpp-notes/01_asm.html)

### Итоговая программа должна быть способна моделировать выполнение программы на низкоуровневом языке (ассемблере) на виртуальном процессоре. Должны быть возможность загрузить программу в память процессора, выполнить ее и наблюдать за изменением состояния процессора (таким как значения регистров) по мере выполнения программы.

### Логика работы процессора:
1. Получение инструкции по адресу счетчика команд (PC)
2. Декодирование инструкции
3. Выполнение инструкции
4. Прибавление к счетачику команды размера выполненноой инструкции

### **Основной поток выполнения:**
- Пользователь предоставляет ассемблерный код, сохраненный в файле.
- Происходит считывание и анализ кода с использованием лексера и парсера (если используется).
- Создаются экземпляры классов команд, операндов и меток на основе анализа кода.
- Программа загружается в память, включая инструкции и операнды.
- Процессор начинает выполнение программы, последовательно считывая и выполняя команды из памяти.
- Каждая команда вызывает соответствующий метод execute(), выполняя свою функцию.
- Выполнение продолжается до завершения программы или обнаружения команды завершения выполнения.

### 3 категории операндов:  
- **Immediate:** начинаются с символа $, за которым следует непосредственное значение в нотации C *(ex: $0x1F, $-577)*
- **Regiter:** значение хранится в указанном регистре *(GPRegister)*
- **Memory *(ссылка на память)*:** определяет адрес ячейки (эффективный адрес)

### Примерная UML-диаграмма необходимых классов
![image](https://github.com/urtoach/lab3oop/assets/115491314/f8da2034-845d-493c-9668-a3a3043529ad)


![image](https://github.com/urtoach/lab3oop/assets/115491314/4872c4e6-e494-4886-88b8-87c635be636c)

***P.s.*** Каждый регистр может хранить 32х разрядное слово, а номер регистра в enum gpr и есть его идентефикатор и номер в блоке регистров

Если строка заканчивается ‘:’ — это метка, которая будет присвоена следующей инструкции.  

![image](https://github.com/urtoach/lab3oop/assets/115491314/16909c4b-43d8-4527-9ca8-08994cd2ffa1)

#### Память (DataMemory)
![image](https://github.com/urtoach/lab3oop/assets/115491314/267264e9-951e-46ce-a83b-b6056e905889)



