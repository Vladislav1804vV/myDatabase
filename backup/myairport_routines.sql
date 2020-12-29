-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: myairport
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Temporary view structure for view `airportcongestion`
--

DROP TABLE IF EXISTS `airportcongestion`;
/*!50001 DROP VIEW IF EXISTS `airportcongestion`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `airportcongestion` AS SELECT 
 1 AS `city`,
 1 AS `airport`,
 1 AS `departures`,
 1 AS `arrivals`,
 1 AS `amount`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `flightoftheheaviestbaggage`
--

DROP TABLE IF EXISTS `flightoftheheaviestbaggage`;
/*!50001 DROP VIEW IF EXISTS `flightoftheheaviestbaggage`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `flightoftheheaviestbaggage` AS SELECT 
 1 AS `id`,
 1 AS `weight`,
 1 AS `city_out`,
 1 AS `city_in`,
 1 AS `model`,
 1 AS `arrivalDate`,
 1 AS `departureDate`*/;
SET character_set_client = @saved_cs_client;

--
-- Final view structure for view `airportcongestion`
--

/*!50001 DROP VIEW IF EXISTS `airportcongestion`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `airportcongestion` AS select `flight`.`city` AS `city`,`flight`.`airport` AS `airport`,count(`flight`.`gate_out`) AS `departures`,count(`flight`.`gate_in`) AS `arrivals`,count(`flight`.`airport`) AS `amount` from (select `city_out`.`name` AS `city`,`airport_out`.`name` AS `airport`,`gate_out`.`number` AS `gate_out`,NULL AS `gate_in` from (((`flights` `flight` join `gates` `gate_out` on((`gate_out`.`id` = `flight`.`gate_id_out`))) join `airports` `airport_out` on((`airport_out`.`code` = `gate_out`.`airport_code`))) join `cities` `city_out` on((`city_out`.`id` = `airport_out`.`city_id`))) union all select `city_in`.`name` AS `city`,`airport_in`.`name` AS `airport`,NULL AS `gate_out`,`gate_in`.`number` AS `gate_in` from (((`flights` `flight` join `gates` `gate_in` on((`gate_in`.`id` = `flight`.`gate_id_in`))) join `airports` `airport_in` on((`airport_in`.`code` = `gate_in`.`airport_code`))) join `cities` `city_in` on((`city_in`.`id` = `airport_in`.`city_id`)))) `flight` group by `flight`.`airport` order by `amount` desc */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `flightoftheheaviestbaggage`
--

/*!50001 DROP VIEW IF EXISTS `flightoftheheaviestbaggage`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `flightoftheheaviestbaggage` AS select `baggage`.`id` AS `id`,`baggage`.`weight` AS `weight`,`city_out`.`name` AS `city_out`,`city_in`.`name` AS `city_in`,`plane`.`model` AS `model`,`flight`.`arrivalDate` AS `arrivalDate`,`flight`.`departureDate` AS `departureDate` from ((((((((((`baggages` `baggage` join `tickets` `ticket` on((`ticket`.`baggage_id` = `baggage`.`id`))) join `sits` `sit` on((`sit`.`id` = `ticket`.`sit_id`))) join `planes` `plane` on((`plane`.`id` = `sit`.`plane_id`))) join `flights` `flight` on((`flight`.`plane_id` = `plane`.`id`))) join `gates` `gate_out` on((`gate_out`.`id` = `flight`.`gate_id_out`))) join `gates` `gate_in` on((`gate_in`.`id` = `flight`.`gate_id_in`))) join `airports` `airport_out` on((`airport_out`.`code` = `gate_out`.`airport_code`))) join `airports` `airport_in` on((`airport_in`.`code` = `gate_in`.`airport_code`))) join `cities` `city_out` on((`city_out`.`id` = `airport_out`.`city_id`))) join `cities` `city_in` on((`city_in`.`id` = `airport_in`.`city_id`))) where (`baggage`.`weight` = (select max(`baggages`.`weight`) from `baggages`)) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-12-25 16:00:17
