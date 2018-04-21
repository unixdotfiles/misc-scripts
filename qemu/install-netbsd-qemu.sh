#!/bin/sh

if [ $# -ne 2 ]
then
  echo "$0 iso image"
  exit 1
fi

iso="$1"
image="$2"

#-net nic,macaddr=ba:be:00:fa:ce:01,model=virtio \
#dd-netdev user,id=vmnic -device virtio-net,netdev=vmnic \

exec qemu-system-x86_64 \
  -usb \
  -nographic \
  -m 1024 \
  -serial 'telnet:127.0.0.1:4444,server' \
  -boot menu=on,order=dc \
  -drive "file=$iso,media=cdrom" \
  -drive "file=$image,cache=writeback" \
  -gdb tcp::4445 \
  -net nic,model=e1000 -net tap,name=tap0,script=no \
  ''
