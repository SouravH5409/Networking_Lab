set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set nf [open sl.nam w]

$ns namtrace-all $nf

set nfl [open sl.tr w]

$ns trace-all $nfl

proc finish { } {
    global ns nfl nf
    $ns flush-trace
    close $nf
    close $nfl
    exec nam sl.nam &
    exit 0
}


set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]

$ns at 0.1 "$n2 label \"CBR\""
$ns at 1.0 "$n0 label \"FTP\""


$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail
$ns duplex-link $n1 $n4 2Mb 10ms DropTail
$ns duplex-link $n3 $n4 2Mb 10ms DropTail
$ns simplex-link $n4 $n5 0.3Mb 100ms DropTail
$ns simplex-link $n5 $n4 0.3Mb 100ms DropTail
$ns duplex-link $n5 $n6 0.5Mb 40ms DropTail
$ns duplex-link $n6 $n8 0.5Mb 30ms DropTail
$ns duplex-link $n5 $n7 0.5Mb 30ms DropTail
$ns duplex-link $n7 $n9 0.5Mb 30ms DropTail

# $ns duplex-link-op $n0 $n1 orient right
# $ns duplex-link-op $n1 $n4 orient right-down
# $ns duplex-link-op $n2 $n3 orient right
# $ns duplex-link-op $n3 $n4 orient right-up
# $ns simplex-link-op $n4 $n5 orient right
# $ns duplex-link-op $n5 $n6 orient right-up
# $ns duplex-link-op $n6 $n8 orient right
# $ns duplex-link-op $n7 $n9 orient right
# $ns duplex-link-op $n5 $n7 orient right-down

$ns queue-limit $n4 $n5 40

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n8 $sink
$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP
$tcp set window_ 8000
$tcp set packetSize_ 552

set udp0 [new Agent/UDP]
$ns attach-agent $n2 $udp0
set null [new Agent/Null]
$ns attach-agent $n9 $null
$ns connect $udp0 $null

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0 
$cbr0 set type_ CBR

$ns at 0.1 "$cbr0 start"
$ns at 0.5 "$ftp start"
$ns at 24.0 "$ftp stop"
$ns at 24.5 "$cbr0 stop"

$ns at 25.0 "finish"

$ns run