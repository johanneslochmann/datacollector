#!/bin/sh

postgresql_autodoc -d forschung -f forschung -h localhost -p 5432 -t html
postgresql_autodoc -d forschung -f forschung -h localhost -p 5432 -t dot
dot -Tsvg -O forschung.dot
