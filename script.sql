CREATE DATABASE `myAirport` ;
USE `myAirport` ;

CREATE TABLE `countries` (
    `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(45) NOT NULL,
    PRIMARY KEY (`id`)
);

CREATE TABLE `cities` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `country_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
    FOREIGN KEY (`country_id`)
    REFERENCES `countries` (`id`)) ;

CREATE TABLE `airports` (
  `code` VARCHAR(4) NOT NULL,
  `name` VARCHAR(45) NOT NULL,
  `type` ENUM("INTL", "DOM") NOT NULL,
  `city_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`code`),
    FOREIGN KEY (`city_id`)
    REFERENCES `cities` (`id`)) ;

CREATE TABLE `gates` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `number` INT UNSIGNED NOT NULL,
  `type` ENUM("SMALL", "LARGE", "MEDIUM") NOT NULL,
  `airport_code` VARCHAR(4) NOT NULL,
  PRIMARY KEY (`id`),
    FOREIGN KEY (`airport_code`)
    REFERENCES `airports` (`code`)) ;

CREATE TABLE `planes` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `model` VARCHAR(45) NOT NULL,
  `tailNumber` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)) ;

CREATE TABLE `flights` (
  `number` VARCHAR(7) NOT NULL,
  `kind` ENUM("REGULAR", "ADDITIONAL", "SPECIAL", "CHARTER") NOT NULL,
  `type` ENUM("NON-STOP", "DOCKING", "STRAIGHT") NOT NULL,
  `status` ENUM("WAIT", "DONE", "CANCEL") NOT NULL,
  `arrivalDate` DATETIME NOT NULL,
  `departureDate` DATETIME NOT NULL,
  `distance` INT NOT NULL,
  `gate_id_in` INT UNSIGNED NOT NULL,
  `gate_id_out` INT UNSIGNED NOT NULL,
  `plane_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`number`),
    FOREIGN KEY (`gate_id_in`)
    REFERENCES `gates` (`id`),
    FOREIGN KEY (`plane_id`)
    REFERENCES `planes` (`id`),
    FOREIGN KEY (`gate_id_out`)
    REFERENCES `gates` (`id`)) ;

CREATE TABLE `sits` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `number` INT UNSIGNED NOT NULL,
  `class` ENUM('A', 'B', 'C') NOT NULL,
  `row` ENUM('1', '2', '3') NOT NULL,
  `costRatio` DOUBLE NOT NULL,
  `plane_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
    FOREIGN KEY (`plane_id`)
    REFERENCES `planes` (`id`)) ;

CREATE TABLE `discounts` (
  `discountСode` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `desription` TEXT(255) NOT NULL,
  `amount` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`discountСode`)) ;

CREATE TABLE `baggages` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `weight` DOUBLE UNSIGNED NOT NULL,
  `volume` DOUBLE UNSIGNED NOT NULL,
  `type` ENUM("CARRYON", "SUITCASE", "ANIMAL") NOT NULL,
  PRIMARY KEY (`id`)) ;

CREATE TABLE `clients` (
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `FIO` VARCHAR(255) NOT NULL,
  `passportData` VARCHAR(100) NOT NULL,
  `age` INT UNSIGNED NOT NULL,
  `gender` ENUM('M', 'F') NOT NULL,
  `account` VARCHAR(45) NOT NULL,
  `ticket_id` INT NOT NULL,
  PRIMARY KEY (`id`)) ;
  
CREATE TABLE `tickets` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `purchaseDate` DATETIME NOT NULL,
  `sit_id` INT UNSIGNED NOT NULL,
  `sales_discountСode` INT UNSIGNED NOT NULL,
  `baggage_id` INT UNSIGNED NOT NULL,
  `client_id` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
    FOREIGN KEY (`sit_id`)
    REFERENCES `sits` (`id`),
    FOREIGN KEY (`sales_discountСode`)
    REFERENCES `discounts` (`discountСode`),
    FOREIGN KEY (`baggage_id`)
    REFERENCES `baggages` (`id`),
    FOREIGN KEY (`client_id`)
    REFERENCES `clients` (`id`)) ;