#!/bin/bash

IPV6_CLIENT="$(pwd)/ipv6_client"

echo executable path $IPV6_CLIENT

$IPV6_CLIENT "This is client1." &
$IPV6_CLIENT "This is client2." &
$IPV6_CLIENT "This is client3." &
$IPV6_CLIENT "This is client4." &
$IPV6_CLIENT "This is client5." &
$IPV6_CLIENT "This is client6." &
$IPV6_CLIENT "This is client7." &
$IPV6_CLIENT "This is client8." &
$IPV6_CLIENT "This is client9." &
$IPV6_CLIENT "This is client10." &
wait
