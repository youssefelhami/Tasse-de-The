<p align="center" name="top">
  <a href="https://github.com/alimgedayad/tasse-de-the/">
    <img src="https://i.postimg.cc/yYRK0gsc/Tesse-de-The-2.png" alt="Tesse de The logo" width="150" height="150">
  </a>
</p>

<h3 align="center">Tasse de Thé</h3>

<p align="center">
      <a href="https://github.com/alimagedayad/tasse-de-the/blob/master/LICENSE" alt="License">
        <img src="https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg"></a>
 </p>
 
<p align="center">
  Tasse de Thé (Cup of Tea) is a todo list with multiple interfaces (C++, JS and PWA).
</p>


## Table of contents

- [Quick start](#quick-start)
  - [Mac/Linux](#mac-or-linux)
  - [Windows](#windows)
- [Documentation](#documentation)
- [Copyright and license](#copyright-and-license)


## Quick Start

#### Mac or Linux

```js
Coming Soon
```

#### Windows

```js
Coming Soon
```

## Documentation
# Introduction
This is the official documentation for Tesse de Thé REST API. Our API aims to provide developers a simple way to consume the most basic features of Todoist API.

# Authentication
None

## Index

  * [Add task](#1-add-task)
  * [[Internal API] Get the latest event ID for C++](#2-[internal-api]-get-the-latest-event-id-for-c++)
  * [Delete ID](#3-delete-task)
  * [Fetch Tasks](#4-fetch-tasks)
  * [Empty List](#5-empty-list)


<br>

--------

<br>

### 1. Add task

***Endpoint:***

```bash
Method: POST
Type: RAW
URL: https://tasse-de-the-web-h5bxp.ondigitalocean.app/task/add
```



***Body:***

```js        
[
    {
        "id": 1,
        "tid": 70,
        "task": "Hi from Postman",
        "category": "pwa",
        "taskPriority": 0,
        "taskDay": 16,
        "taskMonth": 4,
        "taskYear": 2021,
        "taskHour": 1,
        "taskMinute": 30,
        "taskSecond": 0,
        "timestamp": 1618525620127,
        "taskChecked": 0
    }
]
```



***More example Requests/Responses:***


##### I. Example Request: Add task



***Body:***

```js        
[
    {
        "id": 1,
        "tid": 70,
        "task": "Hi from Postman",
        "category": "pwa",
        "taskPriority": 0,
        "taskDay": 16,
        "taskMonth": 4,
        "taskYear": 2021,
        "taskHour": 1,
        "taskMinute": 30,
        "taskSecond": 0,
        "timestamp": 1618525620127,
        "taskChecked": 0
    }
]
```



##### I. Example Response: Add task
```js
{
    "response": "success",
    "code": 200,
    "body": [
        2,
        null,
        "2021-05-16T01:30:00.000Z",
        1618533255549,
        "pwa"
    ]
}
```


***Status Code:*** 0

<br>



### 2. [Internal API] Get the latest event ID for C++



***Endpoint:***

```bash
Method: GET
Type: RAW
URL: https://tasse-de-the-web-h5bxp.ondigitalocean.app/tasks/id
```



***More example Requests/Responses:***


##### I. Example Request: [Internal API] Get the latest event ID for C++



##### I. Example Response: [Internal API] Get the latest event ID for C++
```js
{
    "response": "success",
    "code": 200,
    "body": 2
}
```


***Status Code:*** 0

<br>



### 3. Delete Task


Delete specific task by id and event id


***Endpoint:***

```bash
Method: DELETE
Type: RAW
URL: https://tasse-de-the-web-h5bxp.ondigitalocean.app/task/delete/:id/:eid
```



***URL variables:***

| Key | Value | Description |
| --- | ------|-------------|
| id |  | Entry ID | 
| eid |  | Google's Calendar Event ID | 



***More example Requests/Responses:***


##### I. Example Request: Default



***Query:***

| Key | Value | Description |
| --- | ------|-------------|
| id | 1 | Entry ID |
| eid | 1  | Google's Calendar Event ID |

##### I. Example Response: Default
```js
{
    "response": "success",
    "code": 200,
    "body": null
}
```


***Status Code:*** 0

<br>



### 4. Fetch Tasks


Returning all tasks


***Endpoint:***

```bash
Method: GET
Type: RAW
URL: https://tasse-de-the-web-h5bxp.ondigitalocean.app/tasks/all
```



***More example Requests/Responses:***


##### I. Example Request: Default



***Status Code:*** 0

<br>



### 5. Empty List


Removing all tasks


***Endpoint:***

```bash
Method: POST
Type: RAW
URL: https://tasse-de-the-web-h5bxp.ondigitalocean.app/tasks/delete
```

***More example Requests/Responses:***


##### I. Example Request: Default

```js
{}
```


##### I. Example Response: Default
```js
{
    "response": "success",
    "code": 200,
    "body": null
}
```


***Status Code:*** 0

<br>

Generated at: 2021-04-16 03:03:23 by [docgen](https://github.com/thedevsaddam/docgen)

---


## Copyright and License
Code released under the [Mozilla Public License 2.0 (MPL-2.0)](https://github.com/alimagedayad/tasse-de-the/blob/master/LICENSE).



<a href="#top">Back to top</a>


