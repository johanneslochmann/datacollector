#!/bin/sh

pg_dump -h localhost -p 5432 -d forschung -U jolo -s > crebas.sql
