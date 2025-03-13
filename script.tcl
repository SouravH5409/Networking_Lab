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

$ns at 0.1 "$n1 label \"CBR\""


$ns duplex-link $n0 $n1 10Mb 2ms DropTail

$ns duplex-link-op $n0 $n1 orient right-down




set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set null [new Agent/Null]
$ns attach-agent $n1 $null
$ns connect $udp0 $null
$udp0 set fid_ 2

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0 
$cbr0 set type_ CBR
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.01mb
$cbr0 set random_ false

$ns at 0.1 "$cbr0 start"
$ns at 624.5 "$cbr0 stop"


$ns at 625.0 "finish"

$ns run
