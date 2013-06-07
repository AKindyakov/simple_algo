cat ../README.md

echo ------------------------------------------------------
echo generate makefiles
echo ------------------------------------------------------

rm -r product

echo create product directory
mkdir product/

cd product

cmake ../..

echo ------------------------------------------------------
echo building 
echo ------------------------------------------------------

make
