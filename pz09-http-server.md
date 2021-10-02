## Практическое занятие №9

## HTTP - сервер

На заре развития интернета сайты представляли собой простое хранилище специальным образом размеченных документов и некоторых связанных с ними данных: файлов, изображений и т.п. Для того, чтобы документы могли ссылаться друг на друга и связанные данные был предложен специальный язык гипертекстовой разметки HTML, а для доступа к таким документам посредством сети интернет протокол HTTP. И язык, и протокол, развиваясь и совершенствуясь, дожили до наших дней без существенных изменений.

Протокол HTTP реализован по клиент-серверной технологии и работает по принципу запрос-ответ без сохранения состояния. Целью запроса служит некий ресурс, который определяется **единым идентификатором ресурса** - **URI** (*Uniform Resource Identifier*), HTTP использует дну из разновидностей URI - **URL** (*Uniform Resource Locator*) - **универсальный указатель ресурса**, который помимо сведений о ресурсе определяет также его физическое местоположение.

Задача HTTP-сервера обработать запрос клиента и либо выдать ему требуемый ресурс, либо сообщить о невозможности это сделать. Рассмотрим следующую схему:

![https://interface31.ru/tech_it/images/web-server-structure-001.png](https://interface31.ru/tech_it/images/web-server-structure-001.png)

Пользователь посредством HTTP-клиента, чаще всего это браузер, запрашивает у HTTP-сервера некий URL, сервер проверяет и отдает соответствующий этому URL-файл, обычно это HTML-страница. Полученный документ может содержать ссылки на связанные ресурсы, например, изображения. Если их нужно отображать на странице, то клиент последовательно запрашивает их у сервера, кроме изображений также могут быть запрошены таблицы стилей, скрипты, исполняемые на стороне клиента и т.д. Получив все необходимые ресурсы браузер обработает их согласно кода HTML-документа и выдаст пользователю готовую страницу.

## REST API

REST расшифровывается как REpresentational State Transfer. Это был термин, первоначально введен Роем Филдингом (Roy Fielding), который также был одним из создателей протокола HTTP.  REST - это набор правил (архитектурный стиль) как программисту организовать взаимодействие компонентов распределённого приложения, чтобы все компоненты легко обменивались данными и приложение можно было масштабировать. Не существует «официального» стандарта для RESTful веб-API. Дело в том, что REST является архитектурным стилем, а не протоколом.

Освежим в памяти основные моменты касательно HTTP. [Ресурс](pz08-requests.md#ресурс) - это все, что вы хотите показать внешнему миру через ваше приложение. [URI ресурса](pz08-requests.md#uri-ресурса) - это конечная точка запроса пользователя (endpoint).

### REST и Ресурсы

Важно отметить, что с REST вам нужно думать о приложении с точки зрения ресурсов:

Определите, какие ресурсы вы хотите открыть для внешнего мира

Используйте глаголы, уже определенные протоколом HTTP, для выполнения операций с этими ресурсами.

Вот как обычно реализуется служба REST:

- **Формат обмена данными**: здесь нет никаких ограничений. JSON — очень популярный формат, хотя можно использовать и другие, такие как XML
- **Транспорт**: всегда HTTP. REST полностью построен на основе HTTP.
- **Определение сервиса**: не существует стандарта для этого, а
REST является гибким. Это может быть недостатком в некоторых сценариях,
поскольку потребляющему приложению может быть необходимо понимать
форматы запросов и ответов. Однако широко используются такие языки
определения веб-приложений, как WADL (Web Application Definition
Language) и Swagger.

### Методы HTTP-запроса

Метод, используемый в HTTP-запросе, указывает, какое действие вы хотите выполнить с этим запросом. Важные примеры:

- **GET**: получить подробную информацию о ресурсе
- **POST**: создать новый ресурс
- **PUT**: обновить существующий ресурс
- **DELETE**: Удалить ресурс

## Так что же такое REST API?

REST API —  это прикладной программный интерфейс (API), который использует 
HTTP-запросы для получения, извлечения, размещения и удаления данных. 
Аббревиатура REST в контексте API расшифровывается как «передача состояния представления» (Representational State Transfer). Что это значит? Объясним простыми словами.

Начнем с того, что такое API. Для веб-сайта это код, который позволяет двум программам взаимодействовать друг с другом. API предлагает разработчикам правильный способ написания программы, запрашивающей услуги у операционной системы или другого 
приложения. Проще говоря, это своего рода стандарт, который позволяет программам и приложениям понимать друг друга; это язык интернета, который необходим для работы практически всех сайтов и приложений.

Еще одна распространенная сфера применения — облачные технологии, где REST API нужен для предоставления и организации доступа к веб-службам. Технология позволяет пользователям гибко подключаться к облачным сервисам, управлять ими и взаимодействовать в распределенной среде.

API REST (или RESTful) основан на передаче состояния представлений, архитектурном стиле 
и подходе к коммуникациям, часто используемым при разработке веб-служб.
Некоторые веб-мастера рекомендуют использовать вместо этой технологии SOAP, которая считается более надежной. Но она проигрывает REST API по скорости (последняя использует меньшую пропускную способность, что делает ее более подходящей для эффективного использования интернета).

## Принципы REST API

Принципы REST API определены в диссертации его создателя Роя Филдинга. Основные из них:

- единый интерфейс;
- разграничение клиента и сервера;
- нет сохранения состояния;
- кэширование всегда разрешено;
- многоуровневая система;
- код предоставляется по запросу.

### Единый интерфейс

Ресурсы должны быть однозначно идентифицированы посредством 
одного URL-адреса и только с помощью базовых методов сетевого протокола 
(DELETE, PUT, GET, HTTP).

### Клиент-сервер

Должно быть четкое разграничение между клиентом и сервером:

- пользовательский интерфейс и вопросы сбора запросов — на стороне клиента.
- доступ к данным, управление рабочей нагрузкой и безопасность — на стороне сервера.

### Сохранение состояния

Все клиент-серверные операции должны быть без сохранения 
состояния. Любое необходимое управление состоянием должно осуществляться
 на клиенте, а не на сервере.

### Кэширование

Все ресурсы должны разрешать кэширование, если явно не указано, что оно невозможно.

### Многоуровневая система

REST API допускает архитектуру, которая состоит из нескольких уровней серверов.

### Запрос кода

В большинстве случаев сервер отправляет обратно статические 
представления ресурсов в формате XML или JSON. Однако при необходимости 
серверы могут отправлять исполняемый код непосредственно клиенту.

# Практика

Рассмотрим реализоцию HTTP сервера на С++ на примере библиотеки **crow** ([https://github.com/ipkn/crow](https://github.com/ipkn/crow)). Данная библиотека имеет ряд существенных преимуществ:

- простая в использовании
- очень быстрая
- имеет встроенный парсер JSON
- Header only - при наличии буста в системе необходимо лишь единожды собрать библиотеку, чтобы получить 1 заголовочный файл со всем кодом библиотеки. Никаких линкований, никаких cmake - все предельно просто
- поддерживает Middleware
- поддерживает вебсокеты

На момент августа 2021 года репозиторий имеет 6.4к звезд на GitHub, однако разработчик перестал поддерживать проект около 4 лет назад, поэтому мы будем работать с поддерживаемым сообществом форком - **Crow** ([https://github.com/CrowCpp/Crow](https://github.com/CrowCpp/Crow)).

## Установка

**crow** основан на библиотеке Boost.Asio - кросс-платформенной С++ библиотеки для программирования сетей и некоторых других низкоуровневых программ ввода/вывода.

Поэтому изначально придется поставить boost в систему и другие системные библиотеки, которые требуются для работы библиотеки:

```bash
# ставим boost в систему
sudo apt-get install libboost-all-dev

# зависимости библиотеки
sudo apt-get install build-essential libtcmalloc-minimal4 && sudo ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so
```

Далее можно приступить к установке самой библиотеки:

```bash
# качаем репозиторий с поддерживаемым форком crow
git clone git@github.com:CrowCpp/Crow.git crow

cd crow && mkdir build && cd build
# версия cmake - не меньше 3.15
# cmake --version
cmake ..
make

ls | grep crow_all.h
# crow_all.h

# иначе gcc будет воспринимать библиотеку так, будто бы она написана на С 
mv crow_all.h crow.hpp
mv crow.hpp .. && cd ..
```

Рассмотрим реализацию классического кейса в программировании - Hello world. В нашем случае мы реализуем программу, выполняющую роль HTTP сервера, возращающего 'Hello world' по запросу.

```cpp
// hello_world.cpp
#define CROW_MAIN
#include "crow.hpp"

int main() {
    crow::SimpleApp app;

    /*
     * #define CROW_ROUTE(app, url) app.route<crow::black_magic::get_parameter_tag(url)>(url)
     */
    CROW_ROUTE(app, "/")([]() {
        return "Hello world\n";
    });
    
    app.port(18080) 
            .multithreaded() // приложение будет запущено на всех доступных потоках
            .run();
}
```

```bash
gcc hello_world.cpp crow.hpp -lstdc++ -pthread -o hello_world
./hello_world
```

Проверить работу приложения можно по адресу http://localhost:18080:

```bash
curl http://localhost:18080
# Hello world
```

Теперь напишем приложение, которое будет возвращать HTML страницу с актуальным временем. Также реализуем возможность задавать порт, на котором будет запускаться HTTP сервер:

```cpp
// time_server.cpp
#define CROW_MAIN
#include <chrono>
#include "crow.hpp"

using namespace std::chrono;

int main(int argc, char **argv) {
    int port = argc > 1 ? std::stoi(argv[1]) : 8080;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    .methods("GET"_method)
    ([]() {
        auto now = system_clock::now();
        auto nowInTimeT = std::chrono::system_clock::to_time_t(now);

        std::stringstream strStream;
        strStream << "<html><head><title>HTTPTimeServer powered by Crow C++ Library</title>"
        << R"(<meta http-equiv="refresh" content="1"></head>)"
        << R"(<body><p style="text-align: center; font-size: 48px;">)"
        << std::put_time(std::localtime(&nowInTimeT), "%Y-%m-%d %X")
        << "</p></body></html>";

        return strStream.str();
    });
    app.port(port)
    .multithreaded()
    .run();
}  

// gcc time_server.cpp crow.hpp -lstdc++ -pthread -o time_server
// ./time_server 8000
```

Проверить работу программы можно, открыв в браузере страницу по адресу http://localhost:8000/.

Однако наша программа не совершенна - сейчас она возвращает серверное время, не учитывая часовой пояс (будем считать, что наш сервер расположен в часовом поясе UTC). Исправим это в обновленной версии программы, которая будет принимать параметр timezone, показывающий отклонение в часах часового пояса пользователя от часового пояса UTC.

```cpp
// upd_time_server.cpp
#define CROW_MAIN
#include <chrono>
#include <string>
#include "crow.hpp"

using namespace std::chrono;
using std::string;

int main(int argc, char **argv) {
    int port = argc > 1 ? std::stoi(argv[1]) : 8080;

    crow::SimpleApp app;

    /*
     * #define CROW_ROUTE(app, url) app.route<crow::black_magic::get_parameter_tag(url)>(url)
     */
    CROW_ROUTE(app, "/")
    .methods("GET"_method)
    ([](const crow::request& req) {
        string timezoneDiff("0");
        if (req.url_params.get("timezone")) {
            timezoneDiff = string(req.url_params.get("timezone"));
        }

        auto now = system_clock::now();
        auto nowInTimeT = std::chrono::system_clock::to_time_t(now + std::chrono::hours(std::stoi(timezoneDiff)));

        std::stringstream strStream;
        strStream << "<html><head><title>HTTPTimeServer powered by Crow C++ Library</title>"
        << R"(<meta http-equiv="refresh" content="1"></head>)"
        << R"(<body><p style="text-align: center; font-size: 48px;">)"
        << string("Your timezone: +") + timezoneDiff << string(" hours<br>")
        << std::put_time(std::localtime(&nowInTimeT), "%Y-%m-%d %X")
        << "</p></body></html>";

        return strStream.str();
    });
    app.port(port)
    .multithreaded()
    .run();
}
// gcc upd_time_server.cpp crow.hpp -lstdc++ -pthread -o upd_time_server
// ./upd_time_server 8000
```

Проверить работу программы можно, открыв в браузере страницу по адресу http://localhost:8000/?timezone=3.

Теперь реализуем простое REST API приложение, обеспечивающее работу со списком пользователей, а именно:

- вывод списка всех пользователей
- вывод пользователя по ID
- добавление новых пользователей
- удаление пользователя по ID
- обновление пользователя по ID

Код программы приведен ниже

```cpp
// rest_users.cpp
#define CROW_MAIN
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include "crow.hpp"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;

class UserManager {
private:

    map<int, map<string, string>>  _users;
    set<int> _userIds{};

    int getUniqueId();

public:

    explicit UserManager(const map<int, map<string, string>> &/*users*/);

    crow::json::wvalue getAll() const;

    crow::json::wvalue get(int /*id*/);

    crow::json::wvalue add(const crow::json::rvalue &/*user*/);

    crow::json::wvalue update(int /*userId*/, const crow::json::rvalue &/*user*/);

    crow::json::wvalue remove(int /*id*/);

};

int UserManager::getUniqueId() {
    std::srand(std::time(nullptr));
    int newUserId = std::rand();
    while (_userIds.find(newUserId) != _userIds.end()) {
        newUserId = std::rand();
    }
    _userIds.insert(newUserId);
    return newUserId;
}

UserManager::UserManager(const map<int, map<string, string>> &users) {
    for (auto [id, user] : users) {
        _users[id] = user;
        _userIds.insert(id);
    }
};

crow::json::wvalue UserManager::getAll() const {
    vector<crow::json::wvalue> users;
    for (auto [userId, userMap]: _users) {
        crow::json::wvalue user;

        user["id"] = userId;
        user["firstname"] = userMap["firstname"];
        user["lastname"] = userMap["lastname"];

        users.emplace_back(user);
    }
    return crow::json::wvalue(users);
}

crow::json::wvalue UserManager::get(int id) {
    if (_users.find(id) == _users.end()) {
        crow::json::wvalue response;
        response["status"] = "user with ID " + std::to_string(id) + " does not exist";
        return response;
    }

    crow::json::wvalue user;
    user["id"] = id;
    user["firstname"] = _users[id]["firstname"];
    user["lastname"] = _users[id]["lastname"];
    return user;
}

crow::json::wvalue UserManager::add(const crow::json::rvalue &user) {
    if (!user.has("firstname") || !user.has("lastname")) {
        crow::json::wvalue response;
        response["status"] = "incorrect input data";
        return response;
    }
    int id = getUniqueId();
    _users[id] = map<string, string>{
        {"firstname", user["firstname"].s()},
        {"lastname", user["lastname"].s()}
    };
    crow::json::wvalue response;
    response["status"] = "ok";
    return response;
}

crow::json::wvalue UserManager::update(int userId, const crow::json::rvalue &user) {
    crow::json::wvalue response;
    if (_users.find(userId) == _users.end()) {
        response["status"] = "user with ID " + std::to_string(userId) + " does not exist";
        return response;
    }

    if (user.has("firstname")) {
        _users[userId]["firstname"] = user["firstname"].s();
    }
    if (user.has("lastname")) {
        _users[userId]["lastname"] = user["lastname"].s();
    }

    response["status"] = "ok";
    return response;
}

crow::json::wvalue UserManager::remove(int id) {
    crow::json::wvalue response;
    if (_users.find(id) == _users.end()) {
        response["status"] = "user with ID " + std::to_string(id) + " does not exist";
        return response;
    }
    _users.erase(id);
    response["status"] = "ok";
    return response;
}

int main(int argc, char **argv) {
    int port = argc > 1 ? std::stoi(argv[1]) : 8080;
    map<int, map<string, string>> users{
        {
            1, {
                {"firstname", "Федор"},
                {"lastname", "Достоевский"},
            }
        },
        {
            2, {
                {"firstname", "Александр"},
                {"lastname", "Пушкин"},
            }
        }
    };

    crow::SimpleApp app;
    UserManager userManager(users);

    CROW_ROUTE(app, "/users")
    .methods("GET"_method)
    ([&userManager](const crow::request& req) {
        return userManager.getAll();
    });

    CROW_ROUTE(app, "/users/<int>")
    .methods("GET"_method)
    ([&userManager](int userId) {
        return userManager.get(userId);
    });

    CROW_ROUTE(app, "/users/")
    .methods("POST"_method)
    ([&userManager](const crow::request& req) {
        auto newUser = crow::json::load(req.body);
        auto response = userManager.add(newUser);
        return response;
    });

    CROW_ROUTE(app, "/users/<int>")
    .methods("PUT"_method)
    ([&userManager](const crow::request& req, int userId) {
        auto updatedUser = crow::json::load(req.body);
        auto response = userManager.update(userId, updatedUser);
        return response;
    });

    CROW_ROUTE(app, "/users/<int>")
    .methods("DELETE"_method)
    ([&userManager](int userId) {
        auto response = userManager.remove(userId);
        return response;
    });

    app.port(port)
        .multithreaded()
        .run();
}
// gcc users_rest.cpp crow.hpp  -lstdc++ -pthread -o users_rest
// ./users_rest 8000
```

Проверить работу приложения можно с помощью консольной утилиты curl:

```bash
curl -XGET http://localhost:8000/users
# [{"id":1,"firstname":"Федор","lastname":"Достоевский"},{"lastname":"Пушкин","firstname":"Александр","id":2}]
curl -XDELETE http://localhost:8000/users/1
# {"status":"ok"}
curl -XPOST http://localhost:8000/users/ -d '
{"lastname": "Подвальный", "firstname": "Алексей"}'
# {"status":"ok"}
curl -XGET http://localhost:8000/users
#[{"id":2,"firstname":"Александр","lastname":"Пушкин"},{"lastname":"Подвальный","firstname":"Алексей","id":1232453788}]
```

# Задание

Реализовать REST API приложение для работы с обьектами, хранящимися в базе данных по вариантам по аналогии с тестовым стендом из ПЗ по запросам (rest-example):

```bash
Simple REST API for books

Book struct:

  {
    "id": <str>,
    "title": <str>,
    "author": {
      "firstname": <str>,
      "lastname": <str>
    }
  }

Routes:

  /books - GET
  /books/{id} - GET
  /books - POST
  /books/{id} - PUT
  /books/{id} - DELETE
```

В данном случае имеется 2 сущности - автор и книга (разве что у автора не хватает ID).

Вариант назначается следующим образом - <номер по списку> % <численность группы>.

Варианты:

1. Книга + вложенное поле автор (2 сущности в бд)
2. Пост + вложенное поле автор (2 сущности в бд)
3. Вопрос + вложенное поле тест (2 сущности в бд)
4. Покупатель + вложенное поле товар (2 сущности в бд)
5. Товар + вложенное поле поставщик (2 сущности в бд)
6. Солдат + вложенное поле взвод (2 сущности в бд)
7. Телефон + вложенное поле производитель (2 сущности в бд)
8. Ноутбук + вложенное поле процессор (2 сущности в бд)

Каждая сущность должна иметь не меньше 4 полей. Также должны корректно обрабатываться некорректные запросы (например, GET /books/11 не должен возвращать книгу с ID 11, если таковой нет в базе - должен возвращаться ответ, информирующий об ошибке).



