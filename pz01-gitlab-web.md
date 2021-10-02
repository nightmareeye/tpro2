## Практическое занятие №1

### Знакомство с интерфейсом браузера
1. Win+R, cmd, ping gitwork.ru
1. Эквивалентность gitwork.ru и 10.0.10.56
2. Открытие новых вкладок - правкая кнопка мыши, клик по колёсику.
3. Ctrl+w для закрытия вкладок, ctrl+t для открытия.
4. Ctrl+1 и другие номера для переключения по вкладкам, ctrl+tab, ctrl+shift+tab.
5. Вкладка на пол экрана и win+стрелки.

### Знакомство с GitLab

1. Вы находитесь на сайте локально функционирующего **GitLab**. Его доменное имя https://gitwork.ru, поэтому будем называть его gitlab или gitwork. Это альтернатива онлайн-ресурсу gitlab. Локальный GitLab используется для решения следующих задач:
    * Получения материалов к занятиям. [Здесь](//gitwork.ru/root/help/wikis/%D0%9F%D0%BE%D0%BB%D0%B5%D0%B7%D0%BD%D1%8B%D0%B5-%D1%81%D1%81%D1%8B%D0%BB%D0%BA%D0%B8) приведён перечень дисциплин, которые уже адаптированы для gitwork.
    * Работы с кодом. Проект в GitLab - это либо типовая работа слушателя по дисциплине, либо самостоятельная работа в виде курсового  или дипломного проектирования. Большинство проектов закрыты по ряду соображений, но есть и открытые проекты. Например, такой [диплом](//gitwork.ru/Renzdby/GraphicalNewsExtractor). При использовании gitwork слушатель не привязан к конкретной аудитории и может работать на любом компьютере сети. Кроме того, возможна организация командной разработки.
    * Хранение результатов выполнения заданий в электронном виде и доступ к ним преподавателей

1. Широко используемых систем управления проектам три:
    * GitHub
    * Bitbucket
    * GitLab

    Фактически, github сейчас стал социальной сетью для программистов, различные готовые решения и результаты своих разработок они выкладывают там для общего доступа. В июне 2018 года Microsoft купила GitHub  - это вынуждает искать альтернативы на тот случай, если github будет закрыт или изменится в негативном плане. 

    Из представленных вариантов только у GitLab есть бесплатная версия для локальной установки без использования сети Интернет (так называемый self-hosted вариант). Это позволяет развернуть GitLab в любом подразделении, где есть локальная сеть. Принципы работы со всеми системами одинаковы.

1. GitLab (написан на Ruby и Go.) - это многофункциональный продукт, который включает в себя
    * систему управления репозиториями для системы контроля версий Git - вкладки repository и merge requests слева;
    * вики-систему - вкладка wiki;
    * систему отслеживания ошибок (bug-tracking system, известные примеры таких систем: Redmine, Bugzilla, Atlassian JIRA, YouTrack) -     вкладка issues;
    * систему непрерывной доставки кода (continious integration/continious delivery) - вкладка CI/CD.

    Для каждой из этих функций есть отдельные продукты. Систем контроля версий много (git, mercurial, svn, ...). Есть системы управления репозиториями, которые предоставляют возможность удалённой работы с git-сервером (Gitea, GitWeb, ...). Вики-систем очень много (Wiki.js, DokuWiki, ...), систем отслеживания ошибок много (Jira, YouTrack, ...), систем непрерывной доставки кода много (Jenkins, TeamCity, ...). Системы управления проектами (как GitLab) предоставляют основные функции большинства этих систем. Это удобно, когда всё в одном месте. В некоторый момент времени функционала, встроенного в GitLab может не хватить, тогда можно переходить к осваиванию других продуктов.

    Для каждого вида продуктов альтернативы "разные" по весу. В какой-то области есть однозначный лидер (например, стандарт де-факто в современном мире среди систем контроля версий- это git). В других областях продукты рождаются и умирают. Это естественный процесс, который, однако, заставляет следить за индустрией.


### Первые шаги в GitLab
1. Центральной сущностью GitLab является понятие **проекта**. Проект создаётся пользователем или группой и включает в себя множество файлов (под контролем системы контроля версий git), систему отслеживания ошибок (вкладка issues), и вики-систему. В верху, под меню, указана иерархия Subjects - tpro2 - Repository, то есть вы находитесь в репозитории проекта timp группы "Subjects".

1. У каждого пользователя есть учётная запись (username при регистрации). Если username дописать в адресную строку, вы попадёте в профайл пользователя, например, [https://gitwork.ru/anetto/](//gitwork.ru/anetto/). Откройте эту ссылку в новой вкладке. Посередине страницы вы видите fullname пользователя, дату его регистрации, вкладку activity - на ней цветными квадратиками отражена активность пользователя. Под активностью понимается число его действий по созданию, изменению или удалению текста. Во вкладке **personal projects** вы можете увидеть созданные пользователем проекты. Для anetto это репозитории по нескольким предметам. Зная имя пользователя и название его проекта, легко набрать полный путь [http://gitwork.ru/anetto/timp/](//gitwork.ru/anetto/timp/). 

2. Для создания проектов, не принадлежих конкретному пользователю, можно создавать группу. Например, текущий проект tpro2, создан в группе Subjects. Для того чтобы попасть в проект через адресную строку броузера, можно по аналогии с вышеописанными действиями для пользователя ввести адрес [https://gitwork.ru/sub/tpro2/](//gitwork.ru/sub/tpro2/). Обратите внимание что вместо **subjects** для имени группы указано **sub** - это краткое наименование группы для указания в адресе. Аналогично для того чтобы попасть на страницу самой группы необходимо ввести адрес [https://gitwork.ru/sub/](//gitwork.ru/sub/). На странице группы показаны все проекты, принадлежащие ей.

2. В адресной строке браузера сейчас вы видите **https://gitwork.ru/sub/tpro2/-/blob/master/pz01-gitlab-web.md**, состоящую из:
  * gitwork.ru - доменное имя локального сайта
  * sub - краткое имя группы 
  * tpro2 - название проекта
  * blob - тип отображения записи (например, raw для отображения без форматирования, edit для редактирования, blob при просмотре и другие)
  * master - ветка, для которой отображается файл (термин "ветка" вы узнаете позже при более детальном знакомстве с git)
  * pz01-gitlab-web.md - название того файла, который вы читаете, в данном случае это файл с первым заданием на практическое занятие.

**Следующие действия производите в отдельной вкладке, не закрывая текущую**
1. Если вы еще не зарегистрированы, зарегистрируйте учётную запись, для этого перейдите по ссылке  [https://gitwork.ru/](//gitwork.ru/). Внимательно отнеситесь к правильности full name и остальных полей. Full name служит для удобства других пользователей, которые видят вашу учётную запись. Username используется для входа в систему, и участвует в формировании адреса проекта. **Не забывайте username и пароль**.

1. Создайте проект "timp" ([инструкция по созданию проектов](//gitwork.ru/root/help/wikis/%D0%A1%D0%BE%D0%B7%D0%B4%D0%B0%D0%BD%D0%B8%D0%B5-%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0)) в gitwork.ru. Не выбирайте других имен проекта. Проект всегда можно переименовать, о том как это сделать написано в wiki текущего проекта. Обратите внимание в инструкции указано, что необходимо добавить пользователей - уточните у преподавателя каких пользователей необходимо добавить. В любом случае добавляется администратор **anetto** (anetto\_fullname) с ролью maintainer. В 2021 году преподаватели klexey (kuznetsov), anetto (anetto\_fullname) и barabass (buldyaev).


 **klexey** (kuznetsov) с ролью developer. Галочку initialize with empty readme не нажимать.

1. Изначально на вкладке project показано множество команд для работы с репозиторием. Так как после создания любого файла эта подсказка пропадает, найти их можно будет в файле [git_short.md](//gitwork.ru/sub/timp/blob/master/git_short.md) или [git_full.md](//gitwork.ru/sub/timp/blob/master/git_full.md)

1. Создайте файл readme.md. Этот файл нужен другим людям для знакомства с проектом. Readme.md автоматически показывается пользователю, который зашёл в репозиторий. Например, в текущем проекте в данном файле размещены организационные вопросы и любая другая полезная информация. Для проектов с открытым исходным кодом readme.md содержит небольшое описание проекта, примеры использования, информацию о лицензии и многое другое. Файл readme.md может быть создан для любого каталога проекта, в таком случае он будет отображаться при входе в данный каталог.
    * В меню слева должно быть выбрано project overview -> details (Информация). Посередине экрана вы видите название вашего проекта и множество пиктограмм. Если есть кнопка "Add readme.md" нажите ее, если ее нет, то нажмите New file, в зависимости от версии GitLab это может быть зеленая кнопка New file или кнопка плюс (посередине, где написан адрес), далее new file (новый файл);
    * Ввести имя файла readme.md;
    * В содержимое readme вписать весь текст из таблицы ниже (первую строку нужно поправить в соответствии с написанным в ней)

    ```markdown
    # Сюда впишите ваш fullname, состоящий из года поступления, группы, номера по журналу, первых трех букв фамилии, а также имя - это позволит понять, кто является автором проекта и вам самим убедиться, что вы скачали свой репозиторий. Этот комментарий в вашем репо нужно удалить
    2017-3-07-iva Иван
    ## Это пример заголовка
        
    Здесь могут быть написаны разные вещи. Поддерживается markdown разметка, отсюда и расширение .md
    Обратите внимание, что это продолжение первой строки.
    
    А это строка вторая. Это особенность языка разметки.
    
    Есть списки
    1. Как нумерованные.
    1. Обратите внимание, что число "1" слева при отображении превратится в корректный номер.

    * так и маркированные;
    ```
    * В результате на первой строке должен быть ваш fullname и имени
    * Внизу, в commit message впишите "добавлен readme.md", нажимите **commit changes**;
    * Посмотрите на отображаемое содержимое файла. Обратите внимание на корректную нумерацию в списке и другие изменения;


1. Работа со ссылками
    * Для созданного файла доступны кнопки edit (Редактировать), replace (Заменить), delete (Удалить). Зайдите в edit;
    * Теперь работает подсветка синтаксиса markdown. Подробнее о синтаксисе markdown [тут](//gitwork.ru/help/user/markdown#wiki-specific-markdown);
    * **Обратите внимение на особенность** - если текст не является нумерованным или маркированным списком, то для перевода строки требуется двойное нажаите "Enter"! Сравните текст при редактировании и в самом файле.
    * Добавьте ссылку на файл readme.md в текст своего readme.md. Ссылка на файл должна вести на **содержимое файла readme**, а не в меню его редактирования. Эта ссылка, введённая на новой странице, должна загрузить файл readme.md вашего проекта. (Например, из двух приведенных далее ссылок, одна ведет на файл (blob), а другая на окно его редактирования (edit) для **пользователя los** и его проекта timp: https://gitwork.ru/los/timp/-/blob/master/readme.md и https://gitwork.ru/los/timp/-/edit/master/readme.md)
    * Формат для добавления ссылки
    
    ```
    [текст для показа](сама ссылка)
    ```
    * После добавления ссылки вверху вкладку write переключите на preview. Убедитесь, что ссылка отображается корректно;
    * В commit message впишите "добавлена ссылка на документацию"  и нажмите commit;
    
### Работа с ветками и задачами из web-интерфейса
Git позволяет хранить несколько веток проекта и работать с ними. Функционал веток допускает одновременное наличие разных версий файлов, среди которых можно переключаться. Это фундаментальная сущность при коллективной разработке, подробно мы рассмотрим её далее.

**Ветка 1 - слияние при изменениях только в одной ветке**
1. Снова откройте для редактирования файл readme.md и добавьте строку "Добавлено в ветке branch1".
1. Поле Target branch (ветка) позволяет указать целевую ветку.  Впишите в target branch (ветка) название "branch1" (пробелы не допускаются), галочку "start a new merge request" ("Начать новый запрос на слияние с этих изменений") уберите. Нажмите commit;
1. Теперь вы видите новую редакцию файла. Вверху есть выпадающий список, в котором отображается "branch1". Этот список указывает на текущую ветку с которой ведется работа. Переключите его на master. Это действие вернёт старое содержимое файла, то есть версию файла, соответствующую ветке master. Таким образом, можно иметь две и более версии файла и легко переключаться между ними. При этом каждую из этих версий можно редактировать независимо, а при надобности - слить вместе;
1. Если все выполнено верно, то отличия между файлами readme.md веток master и branch1, заключаются в наличии строчки "Добавлено в ветке branch1" в файле readme.md ветки branch1.
1. На левой вкладке в разделе Repository (Репозиторий) выберите Graph (Диаграмма) - вы увидите визуальное представление веток проекта, сейчас оно не такое наглядное, поскольку ветка branch1 опережает ветку master на одно изменение. Вверху можно выбрать текущую ветку, она будет отображаться краcным цветом на графике.
1. Произведем слияние веток, для этого в левой вкладке найдите и нажмите Merge Requests (Запросы на слияние). Git предоставляет возможность создавать запрос на слияние для только что выполненного изменения (синяя кнопка) или универсальное создание запроса (зеленая кнопка). На новой странице найдите и нажмите кнопку создания нового запроса.  Если выбрали синюю кнопку, то переходите далее, если зеленую, то  необходимо выбрать ветки, которые будут сливаться - в одном выпадаещем списке уже выбрана ветка master, выберите во втором окне ветку branch1, и перейдите к сравнению веток и созданию запроса (зеленая кнопка).
1. В появившемся окне можно описать запрос на слияние, это необходимо для случаев, когда слияние подтверждает другой человек. Ниже в поле Assignee можно указать ответственное лицо за проведение слияния, данный человек должен являться членом текущего проекта. Сейчас это не будем изменять, поскольку вы единственный разработчик своего проекта и можете сами проводить слияние - нажмите кнопку submit merge request (запрос на слияние). Но слияние веток еще не произошло, мы создали только запрос на слияние.
1. В появившемся окне примерно посередине - зеленая кнопка Merge, и галочка "Delete branch" ("Удалить ветку после слияния"). Галочку лучше снять, в противном случае информация о ветке branch1 будет удалена и график будет выглядеть не так наглядно. После нажатия кнопки Merge произойдет слияние веток.
1. После слияния вернитесь в репозиторий, убедитесь, что вы находитесь в ветке master и посмотрите содержимое файла readme.md - в нем добавилась строчка "Добавлено в ветке branch1". Если переключиться в графическое представление веток, то будет видно появление новой ветки, ответвляющейся от основного "ствола" и сливающейся обратно с ним.
    
**Ветка 2 - слияние при пересекающихся изменениях в двух ветках**
1. В рассмотренном примере с веткой 1 производилось слияние веток, в одной из которых не было изменений, поэтому конфликта не возникло. Смоделируем ситуацию с конфликтом.
1. Добавьте в файл readme.md **ветки** branch2 строчку "Добавлено в ветке branch2" (Не забудьте указать правильную ветку и снять метку "начать слияние" перед сохранение файла).
1. Переключитесь на ветку master (новая строчка про branch2 должна пропасть) и добавьте в файл строку "Добавлено в ветке master".
1. Сравните содержимое файлов в ветках master и branch2, а также проверьте визуальное представление - Graph (Диаграмма).
1. Начните слияние веток, после нажатия кнопки submit merge request вы должны попасть на страницу с сообщением "There are merge conflicts" - то есть присутствует конфликт слияния веток.
1. Нажмите кнопку "Resolve Conflicts" ("Разрешить конфликт") - отобразиться содержимое файла readme.md и конфликтующие строки - одна будет обозначена "our changes" - изменения текущей ветки (branch2), другая строка - "their chages" - изменения ветки master. Напротив каждой такой строки будет кнопка "Use ours" или "Use theirs", то есть какое изменение исползовать. Выберете изменения ветки branch2 и нажмите кнопку submit.
1. Завершите слияние - зайдите в список запросов на слияние, выбрав в меню слева "Запросы на слияние" (Merge Requests) и найдите в списке последний запрос, нажмите кнопку Merge
1. Проверьте содержимое файла и посмотрите графическое отображение веток проекта. 
    
**Ветка 3 - слияние при непересекающихся изменениях в двух ветках**
1. Теперь смоделируем ситуацию, когда есть два неконфликтующих изменения.
1. Файл readme.md должен содержать строки "Добавлено в ветке branch1" и "Добавлено в ветке branch2" (или master, если при разрешении конфликта была выбрана другая ветка).
1. В строку с branch1 добавим "изменено в ветке branch3" и сохраним в ветке branch3 (Не забыть ввести имя ветки и снять флажок с формирования запроса на слияние).
1. Вернуться в ветку master и в строку с branch2 (master) добавить "изменено в ветке master".
1. Сравните содержимое файлов веток и графическое представление веток.
1. Начните запрос на слияние веток branch3 и master, конфликта не должно возникнуть.
1. После подтерждения слияния кнопкой merge оба изменения попадут в файл readme.md. Можно в этом убедиться посмотрев его содержание.
1. Посмотрите графическое представление веток проекта.
1. **Проверьте состояние веток проекта через графическое представление - все ветки должны быть слиты с основной веткой master**
    
**Создание и выполнение issue**

Issue - это задачи, тикеты или обсуждения. Предполагается, что любая разработка начинается с постановки задачи (issue). К задаче можно писать комментарии, например, с уточнениями или вариантами решения событий. К задачам относится как разработка нового функционала, так и устранение неисправностей (багов). Выбор тем долгосрочных домашних заданий реализован как отдельное issue для каждой группы.
1. Зайдите во вкладку issues -> list (Обсуждения->Список) **ВАШЕГО** проекта. Нажмите new issue (новое обсуждение) на экране.
 В title (заголовок) впишите "pz01", в description впишите "освоено создание проекта". Поддерживается markdown, preview позволяет посмотреть результат. Внизу есть ссылка на документацию на markdown.
1. В assignee выберите себя. Перед выполнением submit посмотрите на верхний правый угол экрана, где меню на фиолетовом фоне. Выполните submit, и ещё раз посмотрите в верхнее меню. Теперь появилась белая цифра 1 в зеленом кружочке к пиктограмме issue - значит, вы назначены исполнителем для какого-то задания. Зайдите в это задание, и с помощью желтой кнопки close issue отметье его выполненным. Теперь после обновления страницы цифры у issue не будет.
1. Закрытое issue остаётся в общей истории, помеченное закрытым. Для каждого issue можно вести обсуждение (например, для уточнения задания или проблемы).

### Опрос
1. В целях закрепления материала проводится опрос в виде тестов из 5 вопросов. Нельзя использовать internet explorer. На тест даётся 5 минут, ещё 1 дополнительная минута на отправку результатов. По окончании 6 минут результаты отправятся автоматически. Вверху страницы таймер на 5 минут, последняя минута считается отдельно и выделена красным.
2. В начале теста нужно заполнить данные о себе. Это год поступления, последняя цифра номера группы, порядковый номер по журналу (обязательно 2 цифры, слева дополнить нулём. То есть 01, 02, 11, ..), и фамилия на русском языке. К тесту приступать только после заполнения этих данных.
3. Проходить тест можно многократно, но оценивается только первая попытка.
4. [Приступить к опросу по GitLab](http://gitwork.ru:5000/timp3/pz0)

