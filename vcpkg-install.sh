while read package; do
  vcpkg install $(echo $package | cut -d: -f1)
done < installed-packages.txt

