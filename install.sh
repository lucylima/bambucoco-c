GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' 

echo -e "${GREEN}=== Instalador do BambuCoco ===${NC}"

if ! command -v gcc &> /dev/null
then
    echo -e "${RED}Erro: GCC não encontrado. Instale com 'sudo apt install build-essential'${NC}"
    exit 1
fi

echo "📂 Verificando diretórios de dados..."
if [ ! -d "./data/restaurante" ]; then
    mkdir -p ./data/restaurante
    echo "   -> Pasta ./data/restaurante criada."
else
    echo "   -> Pastas já existem."
fi

echo "🔨 Iniciando compilação..."
make install

chmod +x bambucoco

echo -e "${GREEN}=== Instalação Concluída! ===${NC}"
echo "Para rodar, digite: ./bambucoco"