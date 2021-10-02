# Долгосрочное домашнее задание
Группа случайным образом разбивается в подгруппы по 3 человека (возможна одна группа в 2 или 4 человека, чтобы все были в группах).

> Объединение с друзьями чревато конфликтами. Отсюда случайное распределение по группам. Желательно, чтобы уровень программирования в группе был примерно одинаковый

На выбор есть три варианта задания:
1. Игра "[Шашки](ddz/checkers.md)"
1. "[Фоторедактор](ddz/photoeditor.md)"
1. Игра "[Трон 2D](ddz/tron.md)"

Работу вести в совместном Git-репозитории (см. [ПЗ по командной работе](pz04-teamwork.md)). Один из разработчиков выбирается **руководителем** (с ролью maintainer, далее обозначим его как 1), остальные - **разработчиками** (с ролями developer, далее обозначим как 2 и 3). ДДЗ состоит из различных по сложности этапов, каждый этап - это небольшое домашнее задание, которое необходимо сдать **группе**. Начальное состояние репозитория - проект с README.md, в котором изложена цель и указаны роли с номерами разработчиков (использовать только fullname, никаких фамилий) с перечнем функционала для реализации. 

Каждый участник берёт фрагмент функционала из своего перечня и создаёт issue, по номеру этого issue создаёт ветку для разработки (feature-branch). Ветка называется по формату N-feature, например, 3-main-win для issue номер 3 про создание главного окна. Название ветки должно быть максимально коротким, обычно это 1 слово, реже 2. По завершении своего функционала участник создаёт MR, для code review назначается assignee. Для первого MR порядок такой: 1->2->3->1, то есть участник 1 назначает assignee участника 2, участник 2 - участника 3, участник 3 - участника 1. Для второго MR порядок обратный 1<-2<-3<-1. Для третьего MR порядок совпадает с первым. Смысл такого review - чтобы каждый участник ориентировался во всей кодовой базе, а не только в своём фрагменте.

В MR ведётся обсуждение и исправление кода до того момента, пока все замечания reviewer-а не будут устранены. Reviewer должен самостоятельно запустить изучаемую ветку на своей машине и убедиться в работоспособности, в обсуждении указать на проблемы и ошибки. **Ответственность за код, прошедший code review, несёт code reviewer**. Если code reviewer - разработчик, то после одобрения он переводит assingee на руководителя, руководитель завершает merge request путём нажатия merge. Исходная ветка должна быть удалена (галочка при merge).

Когда готов функционал конкретного этапа, руководитель должен собрать общую версию в master и снабдить её аннотированным тэгом по номеру задачи: v1, v2, и так далее. Разработка после этого продолжается, при этом конкретную версию можно сдавать преподавателю. За работоспособность кода при сдаче несёт ответственность руководитель. Преподаватель опрашивает по всему коду любого из участников. Сдача или несдача носит коллективный характер - если один из участников не отвечает, "неуд" получает вся группа.

README должен содержать описание текущего этапа, инструкции по установке, запуску и проверке работоспособности. Совет - инструкции по проверке работоспособности писать в самом начале этапа, чтобы каждый понимал - что должно быть в результате.