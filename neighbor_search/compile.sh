cd build
make 2>../err
cd ..
echo "err:"
cat err
rm -rf err
