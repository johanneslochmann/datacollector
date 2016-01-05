#!/bin/sh

/usr/bin/pg_dump --host localhost --port 5432 --username "jolo" --no-password  --format custom --blobs --verbose --file "/home/jolo/projects/datacollector/database/forschung.backup" "forschung"
