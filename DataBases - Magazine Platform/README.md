# Digital Magazine Subscription Database

> A comprehensive Oracle SQL relational database system modeling a digital magazine distribution platform. Designed to showcase advanced database architecture, query optimization, and transaction management.

## Overview

This project simulates the core backend data infrastructure of a digital publishing platform connecting readers with publishers. It handles end-to-end data workflows including user registration, catalog management, subscription tracking, automated invoice generation, and user reviews. 

Built from the ground up, this repository covers the entire database lifecycle: from conceptual Entity-Relationship (ER) modeling and normalization to execution plan optimization and concurrency control.

## Technical Skills

* **Database Design & Architecture:** 
  * Full Entity-Relationship modeling translated into a robust relational schema.
  * Strict normalization up to the Third Normal Form (3NF) to eliminate redundancies, accompanied by theoretical expansions into BCNF, 4NF, and 5NF.
  * Strategic denormalization applied to improve read performance (e.g., tracking article counts per edition).
* **Advanced Querying:** 
  * Complex data retrieval using synchronized and unsynchronized subqueries, Common Table Expressions (`WITH` clause), and Outer Joins.
  * Analytical implementations including Top-N analysis, Relational Division, and conditional aggregations using `DECODE`, `NVL`, and `CASE`.
* **Performance Tuning & Optimization:** 
  * Deep analysis of execution plans using `EXPLAIN PLAN` and `DBMS_XPLAN`.
  * Query optimization through strategic Index creation (`INDEX RANGE SCAN`) and the application of optimizer hints (e.g., `/*+ USE_NL */`) to force Nested Loops over less efficient Table Access methods.
* **Data Integrity & Security:** 
  * Enforcement of domain integrity using `PRIMARY KEY`, `FOREIGN KEY`, `UNIQUE`, and `CHECK` constraints.
  * Implementation of sequences for automated surrogate key generation.
  * Creation of complex Views protecting underlying table structures while managing permitted/restricted DML operations.
* **Transaction Management & Concurrency:** 
  * Practical demonstration of ACID properties through concurrent transaction simulation.
  * Testing and documenting the effects of various Isolation Levels (`READ COMMITTED`, `SERIALIZABLE`) on phantom reads and data consistency.

## Schema Overview

The database models a highly relational ecosystem comprising 11 core tables:
* **Core Entities:** `UTILIZATOR` (Users), `EDITURA` (Publishers), `REVISTA` (Magazines), `EDITIE` (Editions), `ARTICOL` (Articles), `AUTOR` (Authors).
* **Transactions & Metrics:** `ABONAMENT` (Subscriptions), `FACTURA` (Invoices), `RECENZIE` (Reviews), `TIP_ABONAMENT` (Subscription Types).

##  Getting Started

*(The SQL scripts are written for Oracle Database. Run the provided DDL/DML scripts in SQL*Plus or Oracle SQL Developer to instantiate the schema and populate the mock data.)*
