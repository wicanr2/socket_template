MUDP_CLIENT="$(pwd)/m_udp_client"

echo executable path $MUDP_CLIENT

$MUDP_CLIENT "225.0.0.10" 8888 "member 1 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 2 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 3 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 4 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 5 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 6 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 7 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 8 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 9 broadcast." &
$MUDP_CLIENT "225.0.0.10" 8888 "member 10 broadcast." &
wait
