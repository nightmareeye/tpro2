## Практическое занятие №8. Работа с HTTP-серверами


### HTTP

Когда вы вводите в браузере URL-адрес, например [www.google.com](https://www.google.com/), на сервер отправляется запрос на веб-сайт, идентифицированный URL-адресом.

Затем этот сервер формирует и выдает ответ. Важным является формат этих запросов и ответов. Эти форматы определяются протоколом **HTTP — Hyper Text Transfer Protocol.**

Этот протокол описывает взаимодействие между двумя компьютерами (клиентом и сервером), построенное на базе сообщений, называемых запрос (Request) и ответ (Response). Каждое сообщение состоит из трех частей: стартовая строка, заголовки и тело. При этом обязательной является только стартовая строка.

Когда вы набираете URL в браузере, он отправляет запрос GET на указанный сервер. Затем сервер отвечает HTTP-ответом, который содержит данные в формате **HTML — Hyper Text Markup Language**. 

Затем браузер получает этот HTML-код и отображает его на экране. Допустим, вы заполняете форму, присутствующую на веб-странице, со списком элементов. В таком случае, когда вы нажимаете кнопку «**Submit**» (Отправить), HTTP-запрос **POST** отправляется на сервер.

Рассмотрим несколько ключевых абстракций HTTP.

### Ресурс

Ресурс — это ключевая абстракция, на которой концентрируется протокол HTTP. Ресурс — это все, что вы хотите показать внешнему миру через ваше приложение. Например, если мы пишем приложение для управления задачами, экземпляры ресурсов будут следующие:

- Конкретный пользователь
- Конкретная задача
- Список задач

### URI ресурса

Когда вы разрабатываете RESTful сервисы (чуть подробнее о них - в следующем ПЗ или [статье](https://habr.com/ru/company/yandex/blog/265569/)), вы должны сосредоточить свое 
внимание на ресурсах приложения. Способ, которым мы идентифицируем 
ресурс для предоставления, состоит в том, чтобы назначить ему URI — 
универсальный идентификатор ресурса. Например:

- Создать пользователя: **POST /users**
- Удалить пользователя: **DELETE /users/1**
- Получить всех пользователей: **GET /users**
- Получить одного пользователя: **GET /users/1**

### Компоненты HTTP

HTTP определяет следующую структуру запроса:

- строка запроса (**request line**) — определяет тип сообщения
- заголовки запроса (**header fields**) — характеризуют тело сообщения, параметры передачи и прочие сведения
- тело сообщения (**body**) — необязательное

HTTP определяет следующую структуру ответного сообщения (response):

- строка состояния (**status line**), включающая код состояния и сообщение о причине
- поля заголовка ответа (**header fields**)
- дополнительное тело сообщения (**body**)

### Методы HTTP-запроса

Метод, используемый в HTTP-запросе, указывает, какое действие вы хотите выполнить с этим запросом. Важные примеры:

- **GET**: получить подробную информацию о ресурсе
- **POST**: создать новый ресурс
- **PUT**: обновить существующий ресурс
- **DELETE**: Удалить ресурс

### Код статуса ответа HTTP

Код состояния всегда присутствует в ответе HTTP. Типичные примеры:

### Пример HTTP-взаимодействия

Рассмотрим пример.

Запрос:

```
GET /index.php HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (X11; U; Linux i686; ru; rv:1.9b5) Gecko/2008050509 Firefox/3.0b5
Accept: text/html
Connection: close

```

Первая строка — это строка запроса, остальные — заголовки; тело сообщения отсутствует

Ответ:

```
HTTP/1.0 200 OK
Server: nginx/0.6.31
Content-Language: ru
Content-Type: text/html; charset=utf-8
Content-Length: 1234
Connection: close

... САМА HTML-СТРАНИЦА ...

```

# Практика

## Рабочее окружение

Для тренировки будем использовать простое REST API приложение, обеспечивающее работу с набором книг. Для его запуска необходимо проделать следующие шаги:

```bash
# найти на рабочих машинах файл с заархивированным докер образом приложения - rest-example.tar
# загрузить докер образ
docker load < rest-example.tar

# проверяем наличие образа
docker images | grep rest-example

# запускаем приложение на 8000 порту хостовой машины
docker run --name rest-example -d -p 0.0.0.0:8000:8000 rest-example

# информация о стенде
docker logs rest-example

# проверяем корректность работы
curl -XGET http://localhost:8000/books/1
# {"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}}  
```

В приложении реализованы следующие эндпоинты:

```
/books - GET - возвращает JSON со всеми книгами
/books/{id} - GET - возвращает JSON с книгой по ее ID
/books - POST - добавляет книгу с параметрами переданного JSON
/books/{id} - PUT - изменяет существующую книгу с заданным ID
/books/{id} - DELETE - удаляет книгу по заданному ID
```

Предполагается, что работа ведется на машинах с ОС Linux, дистрибутив Ubuntu (хотя в целом это не принципиально).

## А что по плюсам?

Существует несколько вариантов реализации сетевых запросов. Рассмотрим некоторые из них.

### Pure C++

Берем чистые плюсы (а лучше даже С) и с помощью сокетов совершаем запросы к сетевым ресурсам. В данном случае нам придется самим формировать тела запросов, декодировать и кодировать данные и тд. Пример всего этого безобразия приведен ниже (слегка избыточно, но зато достаточно наглядно):

```cpp
// get_requester.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using std::string;

string getProtocol(const string& url) {
    string protocol;

    for (int i = 0; i < url.size(); i++) {
        if (url[i] != '/' || url[i + 1] != '/') {
            protocol += url[i];
        } else {
            protocol += "//";
            break;
        }
    }

    return protocol;
}

string getHost(string url, string& port) {
    string host;

    url.replace(0, getProtocol(url).size(), "");

    for (char ch : url) {
        if (ch == '/') {
            break;
        } else {
            host += ch;
        }

    }

    if (url.find(':') != -1) {
        host = url.substr(0, url.find(':'));
        port = url.substr(url.find(':') + 1, url.find('/'));
    }

    return host;
}

string getAction(string url) {
    string parm;
    string port;

    url.replace(0, getProtocol(url).size() + getHost(url, port).size(), "");
    url = url.substr(url.find('/'));

    for (char ch : url) {

        if (ch != '?' && ch != '#') {
            parm += ch;
        } else {
            break;
        }

    }

    return parm;
}

string getParams(const std::vector<std::pair<string, string> > &requestData) {
    string parm;

    for (auto &itr : requestData) {
        if (parm.empty()) {
            parm += "";
        } else {
            parm += "&";
        }
        parm += itr.first + "=" + itr.second;
    }

    return parm;
}

string GET(const string &url, const std::vector<std::pair<string, string> > &requestData) {
    string protocol = getProtocol(url);
    string port = "80";
    string host = getHost(url, port);
    string script = getAction(url);
    string params = getParams(requestData);
    string action = script + (params.empty() ? "" : "?" + params);

    char buf[1024 * 1024];

    string header;

    header += ("GET " + action + " HTTP/1.1\n");
    header += ("Host: " + host + "\n\n");

    std::cout << header << std::endl;

    int sock;
    struct sockaddr_in addr{};
    struct hostent *raw_host;
    raw_host = gethostbyname(host.c_str());
    if (raw_host == nullptr) {
        std::cout << "ERROR, no such host";
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(port));

    bcopy((char *) raw_host->h_addr, (char *) &addr.sin_addr, raw_host->h_length);

    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cerr << "connect error" << std::endl;
        exit(1);
    }

    send(sock, header.c_str(), header.size(), 0);
    recv(sock, buf, sizeof(buf), 0);

    string answer;

    for (char j : buf) {
        if (j == '\0') {
            break;
        }
        answer += j;
    }

    return answer;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Incorrect params count. Usage: " << std::endl
                  << "get_requester <url>";
        exit(1);
    }
    string url(argv[1]);
    auto response = GET(url, {});
    std::cout << response << std::endl;
    return 0;
}

```

Что здесь происходит? На самом деле, все достаточно просто (хоть и массивно):

- из заданного URL извлекается протокол запроса (http/https), хост сетевого ресурса, его порт и непосредственно сетевой ресурс, к которому мы хотим получить доступ
- далее в переменной `header`формируется минимальное тело GET запроса к сетевому ресурсу
- потом начинается чистый C и работа с сокетами - зная порт и хост, мы создаем сокет, обеспечивающий соединение с сетевым ресурсом, и передаем ему через `send` полезную нагрузку, сформированную в переменной `header`
- далее с помощью `recv` мы получаем ответ от сервера, представленный в виде полезной слежубной информации протокола и полезной нагрузки, и выводим его на экран

Попробуем опробовать все это на практике:  

```bash

# Компилируем наше приложение для GET запросов
# -l<имя_библиотеки> - флаг, позволяющий слинковать библиотеку. В нашем случае
# это stdc++ - стандартная библиотека C++
gcc get_requester.cpp -o get_requester -lstdc++ 

# Получаем слежубную информацию и полезную нагрузку, представленную  
# json строкой с интересующей нас книгой
./get_requester http://localhost:8000/books/1
# HTTP/1.1 200 OK
# Content-Type: application/json
# Date: Fri, 06 Aug 2021 18:35:52 GMT
# Content-Length: 102

# {"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}}
```

### cURL

Использовать cURL. Тут дела обстоят получше - нам уже не надо ручками парсить страшные URL и самостоятельно формировать запросы - на себя это берет библиотка libcurl. Реализуем приложение с аналогичным функционалом, но уже с использованием cURL:

```cpp
// get_requester2.0.cpp
#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Incorrect params count. Usage: " << std::endl
        << "get_requester2.0 <url>";
        exit(1);
    }

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    return 0;
}
```

Так как в данном случае мы работаем с библиотекой libcurl, ее предварительно необходимо поставить в систему и при компилировании программы явно слинковать:

```bash

# ставим libcurl в систему
apt-get install libcurl4-gnutls-dev

# теперь кроме libstdc++ мы линкуем еще curl
gcc get_requester2.0.cpp -o get_requester2.0 -lcurl -lstdc++

# в данном случае служебная информации протокола уже не выводится - 
# при желании мы можем получить ее из переменной curl
./get_requester2.0 http://localhost:8000/books/1
# {"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}}
```

Как видно, кода стало в 5 раз меньше, но во времена 21 стандарта С++ и ООП процедурное программирование в С++ уже выглядит скорее пережитком, нежели чем хорошим вариантом. Поэтому далее мы рассмотрим cpr - библиотеку "обертку" над cURL, предоставляющую удобный интерфейс для совершения запросов

### cpr

C++ Requests: Curl for People ([https://github.com/whoshuu/cpr](https://github.com/whoshuu/cpr)) - название бибиотеки хорошо отображает ее суть. Рассмотрим ее работу на том же примере: 

```cpp
// get_requester3.0.cpp
#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Incorrect params count. Usage: " << std::endl
                  << "get_requester3.0 <url>";
        exit(1);
    }

    cpr::Response r = cpr::Get(cpr::Url{argv[1]});
    std::cout << r.text << std::endl;
    return 0;
}
```

Как видно, в данном случае запрос выполняется в 1 строчку. Очень удобно. Однако за любое удобство приходится платить цену - в данном случае это выражается в сложности сборки. Для сборки приложения воспользуеися инструментом cmake.

Рассмотрим установку самой библиотеки. Самым удобном способом является использование механизма сабмодулей:

```cpp
# инициализируем git репозиторий
git init

# добавляем библиотеку в качестве сабмодуля
git submodule add https://github.com/whoshuu/cpr.git

# у нас появился следующий файл
cat .gitmodules
# [submodule "cpr"]
#         path = cpr
#         url = https://github.com/whoshuu/cpr.git

# в случае работы в классе можно просто скопировать папку библиотеки (папка cpr)
# в рабочую папку с кодом 
```

Далее формируем CMakeList.txt с кодом сборки приложения:

```bash
cmake_minimum_required(VERSION 3.15)
project(get_requester3.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(get_requester3.0 get_requester3.0.cpp)

add_subdirectory(cpr) # указываем папку с библиотекой
include_directories(${CPR_INCLUDE_DIRS}) # линкуем файлы с исходным кодом библиотеки
target_link_libraries(get_requester3.0 ${CPR_LIBRARIES}) # линкуем саму библиотеку
```

Далее необходимо собрать проект. Сначала будет собрана сама библиотека, далее будет собрано само приложение:

```bash
mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

./get_requester3.0 http://localhost:8000/books/1
# {"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}
```

В документации библиотеки ([https://whoshuu.github.io/cpr/](https://whoshuu.github.io/cpr/)) указано, как совершать запросы других типов. Приведем пример добавления новой книги в случае нашего REST приложения:

```cpp
// add_book.cpp
#include <iostream>
#include <cpr/cpr.h>

int main(int argc, char** argv) {
    cpr::Response r = cpr::Post(cpr::Url{"http://localhost:8000/books"},
                                cpr::Body{"{\"title\":\"Хаджи-Мурат\",\"author\":{\"firstname\":\"Лев\",\"lastname\":\"Толстой\"}}"});
    std::cout << r.text << std::endl;

    return 0;
}
```

```bash
./get_requester3.0 http://localhost:8000/books
#[{"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}},{"id":"2","title":"Преступление и наказание","author":{"firstname":"Фёдор","lastname":"Достоевский"}}]

./add_book

./get_requester3.0 http://localhost:8000/books
#[{"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}},{"id":"2","title":"Преступление и наказание","author":{"firstname":"Фёдор","lastname":"Достоевский"}},{"id":"498081","title":"Хаджи-Мурат","author":{"firstname":"Лев","lastname":"Толстой"}}]
```

В данном случае мы совершили POST запрос, передав в полезной нагрузке новую книгу, которая была успешно добавлена.

### JSON for Modern C++

Как видно, общение с нашим REST сервисом происходит путем передачи данных в формате JSON (JavaScript Object Notation), который является одним из основных форматов передачи данных по сети.

В С++ (в 2021 году) до сих пор нет встроенных библиотек для работы с JSON, однако существует библиотека ([https://github.com/nlohmann/json](https://github.com/nlohmann/json)), которая реализует максимально удобный интерфейс для работы с json обьектами. Рассмотрим некоторые ее особенности:

- возможно подключение в виде 1 заголовочного файла. Никаких cmake, никаких линкований - просто импортировали и начали использовать.
- поддерживает интерфейс STL контейнеров.

Обновим наш CMakeList.txt и продемонстрируем работу с данной библиотекой на конкретных примерах:

```bash
cmake_minimum_required(VERSION 3.15)
project(get_requester3.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(get_requester3.0 get_requester3.0.cpp json.hpp) # добавили библиотеку json

add_subdirectory(cpr) # указываем папку с библиотекой
include_directories(${CPR_INCLUDE_DIRS}) # линкуем файлы с исходным кодом библиотеки
target_link_libraries(get_requester3.0 ${CPR_LIBRARIES}) # линкуем саму библиотеку
```

Данный код получает список книг и выводит их в стандартный поток вывода:

```cpp
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/books"});
    auto books = json::parse(r.text);

    for (auto book : books) {
        auto authorFirstName = book["author"]["firstname"].get<std::string>();
        auto authorLastName = book["author"]["lastname"].get<std::string>();
        auto bookTitle = book["title"].get<std::string>();
        
        std::cout << "Автор: " << authorFirstName << " " << authorLastName << std::endl
                  << "Книга: " << bookTitle << std::endl << std::endl;
    }

    return 0;
}

# Автор: Лев Толстой
# Книга: Война и Мир

# Автор: Фёдор Достоевский
# Книга: Преступление и наказание
```

Данный код добавляет книги в список книг и далее удаляет одну из них:

```cpp
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

void printBooks() {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/books"});
    auto books = json::parse(r.text);

    for (auto book : books) {
        auto bookId = book["id"].get<std::string>();
        auto authorFirstName = book["author"]["firstname"].get<std::string>();
        auto authorLastName = book["author"]["lastname"].get<std::string>();
        auto bookTitle = book["title"].get<std::string>();

        std::cout << "Автор: " << authorFirstName << " " << authorLastName << std::endl
        << "Книга: " << bookTitle << "(ID " << bookId << " )" << std::endl << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "Before: " << std::endl;
    printBooks();

    json newBook{
        {"author", {
            {"firstname", "Name"},
            {"lastname", "Lastname"}
        }},
        {"title", "Book title"}
    };
    auto anotherNewBook = R"(
      {
        "author": {
          "firstname": "Another author name",
          "lastname": "Another author lastname"
        },
        "title": "Another book title"
      }
    )"_json;

    cpr::Post(cpr::Url{"http://localhost:8000/books"},
              cpr::Body{newBook.dump()});
    cpr::Post(cpr::Url{"http://localhost:8000/books"},
              cpr::Body{anotherNewBook.dump()});

    std::cout << "After adding: " << std::endl;
    printBooks();

    std::string deletedBookID("1");
    cpr::Delete(cpr::Url{"http://localhost:8000/books/" + deletedBookID});

    std::cout << "After deleting book with ID 1: " << std::endl;
    printBooks();

    return 0;
}
```

Ниже представлен вывод работы программы:

```bash
Before: 
Автор: Лев Толстой
Книга: Война и Мир(ID 1 )

Автор: Фёдор Достоевский
Книга: Преступление и наказание(ID 2 )

After adding: 
Автор: Лев Толстой
Книга: Война и Мир(ID 1 )

Автор: Фёдор Достоевский
Книга: Преступление и наказание(ID 2 )

Автор: Name Lastname
Книга: Book title(ID 498081 )

Автор: Another author name Another author lastname
Книга: Another book title(ID 727887 )

After deleting book with ID 1: 
Автор: Фёдор Достоевский
Книга: Преступление и наказание(ID 2 )

Автор: Name Lastname
Книга: Book title(ID 498081 )

Автор: Another author name Another author lastname
Книга: Another book title(ID 727887 )

```

Также  библиотека поддерживает удобную сериализацию и десериализацию json объектов:

```cpp
#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
    std::string filename = "books.json";

    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/books"});
    auto books = json::parse(r.text);

    auto ofBooks = std::fstream(filename);
    ofBooks << books << std::endl;;

    auto ifBooks = std::ifstream(filename);

    json loadedBooks;
    ifBooks >> loadedBooks;

    loadedBooks.emplace_back(R"(
      {
        "author": {
          "firstname": "Another author name",
          "lastname": "Another author lastname"
        },
        "title": "Another book title"
      }
    )"_json);

    std::cout << loadedBooks.dump(4) << std::endl;

    return 0;
}
```

Вывод программы представлен ниже:

```bash
[
    {
        "author": {
            "firstname": "Лев",
            "lastname": "Толстой"
        },
        "id": "1",
        "title": "Война и Мир"
    },
    {
        "author": {
            "firstname": "Фёдор",
            "lastname": "Достоевский"
        },
        "id": "2",
        "title": "Преступление и наказание"
    },
    {
        "author": {
            "firstname": "Another author name",
            "lastname": "Another author lastname"
        },
        "title": "Another book title"
    }
]

```

# Задание

Необходимо сделать скриншоты, демонстрирующие работу программы в соответствии с заданием. При этом после каждого действия должен выводиться лог вида (Формат поля <action> на ваше усмотрение):
```bash
<gitlab username>: <action>
```

Например:
```bash
books_manager delete 1
# 2017-3-08-kor: deleted book with ID 1
```


На основе сервиса по работе с книгами, реализовать приложение, которое:

- считывает книги из текстовых файлов заданного формата и добавляет их в список книг

```bash
cat books.json
# [
#  {
#    "author": {
#      "firstname": "Имя автора книги",
#      "lastname" "Фамилия автора книги"
#     },
#     "title": "Название книги"
#  },
#  {
#    "author": {
#      "firstname": "Александр",
#      "lastname" "Пушкин"
#     },
#     "title": "Евгений онегин"
#  }
# ]
./books_manager load_file books.json
```

- удаляет книги  по заданному ID

```bash
./get_requester3.0 http://localhost:8000/books
#[{"id":"1","title":"Война и Мир","author":{"firstname":"Лев","lastname":"Толстой"}},{"id":"2","title":"Преступление и наказание","author":{"firstname":"Фёдор","lastname":"Достоевский"}}]

./books_manager delete 1

./get_requester3.0 http://localhost:8000/books
#[{"id":"2","title":"Преступление и наказание","author":{"firstname":"Фёдор","lastname":"Достоевский"}}]
```

- обновляет добавленные книги по заданному ключу на основе файла с книгой или непосредственно самих данных в текстовом виде (реализовать оба варианта)

```bash
./get_requester3.0 http://localhost:8000/books/2
#{"id":"2","title":"Преступление и наказание","author":{"firstname":"Фёдор","lastname":"Достоевский"}}

./books_manager update 2 '{"title":"Преступление и что-то там","author":{"firstname":"Фёдор","lastname":"Достоевский"}}'
# ./books_manager update_from_file 2 book.json
# cat book.json
# {
#    "author": {
#      "firstname": "Фёдор",
#      "lastname" "Достоевский"
#     },
#     "title": "Преступление и что-то там"
#  }

./get_requester3.0 http://localhost:8000/books/2
#{"id":"2","title":"Преступление и что-то там","author":{"firstname":"Фёдор","lastname":"Достоевский"}}
```

Дополнительное задание - реализовать программу, выводящую список общих друзей пользователей из соц сети ВК по их заданным ID

