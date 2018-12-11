CREATE DATABASE MARKETING;

USE MARKETING;

CREATE TABLE AREAS(
`ID_AREA` INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
`NOMBRE` VARCHAR(40) NOT NULL,
`ENCARGADO` VARCHAR(40) NOT NULL);

CREATE TABLE ETHERSHIELD(
`MAC` VARCHAR(30)  PRIMARY KEY UNIQUE NOT NULL,
`ID_AREA` INT NOT NULL,
`FECHA` DATE);

CREATE TABLE SENSOR_ULTRASONICO(
`ID_ULTRA` INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
`FECHA` DATE NOT NULL,
`TIEMPO`VARCHAR(255),/*CHECAR EL FORMATO DE TIEMPO DE ESPERA*/
`MAC` VARCHAR(30) NOT NULL);

CREATE TABLE SENSOR_TEMPERATURA(
`ID_TEMP` INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
`FECHA` DATE NOT NULL,
`HUMEDAD` VARCHAR(255),/*CHECAR QUE TIPO DE VALOR REGRESA HUMEDAD*/
`TEMPERATURA` VARCHAR(255),
`MAC` VARCHAR(30) NOT NULL);

CREATE TABLE SENSOR_INFRARROJO(
`ID_INFRA` INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
`FECHA` DATE NOT NULL,
`CANTIDAD_P` INT NOT NULL,
`MAC` VARCHAR(30) NOT NULL);

CREATE TABLE ESTADISTICA(
`ID_ESTAD` INT PRIMARY KEY AUTO_INCREMENT NOT NULL,
`MAC` VARCHAR(30) NOT NULL,
`ID_ULTRA` INT NOT NULL,
`ID_INFRA` INT NOT NULL,
`ID_TEMP` INT NOT NULL);

