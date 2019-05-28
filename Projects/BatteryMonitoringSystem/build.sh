#!/bin/sh

mkdir -p output

xc8 --chip=16f886 --outdir="./output" *.c
