// QUESTÃO 3
import java.util.Scanner;
public class Energia {
    public static void main (String args[]) {
        float consumo, custo_consumo, valor_fixo, valor_total;
        valor_fixo = 5f;
        
        Scanner entrada = new Scanner(System.in);
        consumo = entrada.nextFloat();
        
        if(consumo <= 500){
            custo_consumo = (float)consumo * 0.02f;
            valor_total = custo_consumo + valor_fixo;
            System.out.printf("%.2f %.2f %.2f", custo_consumo, valor_fixo, valor_total);
        } else if (consumo > 500 && consumo <= 1000) {
            custo_consumo = 500f * 0.1f;
            custo_consumo += ((float)consumo - 500f) * 0.05f;
            valor_fixo = 5f;
            valor_total = custo_consumo + valor_fixo;
            System.out.printf("%.2f %.2f %.2f", custo_consumo, valor_fixo, valor_total);
        } else {
            custo_consumo = 1000f * 0.35f;
            custo_consumo += ((float)consumo - 1000f) * 0.1f;
            valor_fixo = 5f;
            valor_total = custo_consumo + valor_fixo;
            System.out.printf("%.2f %.2f %.2f", custo_consumo, valor_fixo, valor_total);
        }
        entrada.close();
    }
}



// QUESTÃO 4
import java.util.Scanner;
public class Festa {
    public static void main(String[] args) {
        int qnt_homens = 0, qnt_mulheres = 0;
        float valor_homens = 0, valor_mulheres = 0;

        Scanner entrada = new Scanner(System.in);

        while (true) {
            char dado = entrada.next().charAt(0);

            if (dado == 'h') {
                qnt_homens += 1;
                valor_homens += 12.5f;
            } else if (dado == 'm') {
                qnt_mulheres += 1;
                valor_mulheres += 7.4f;
            } else if (dado == 'q') {
                break;
            }
        }

        System.out.println(qnt_homens + " " + qnt_mulheres);
        System.out.printf("%.2f %.2f %.2f", valor_homens, valor_mulheres, valor_homens + valor_mulheres);

        entrada.close();
    }
}



// QUESTÃO 5
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;
public class Loja {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        int n = Integer.parseInt(entrada.nextLine());
        Map<String, Integer> estoque = new LinkedHashMap<>();
        for (int i = 0; i < n; i++) {
            String nomeProduto = entrada.next();
            int quantidade = entrada.nextInt();
            estoque.put(nomeProduto, quantidade);
            entrada.nextLine();
        }

        while (true) {
            String nomeProdutoVenda = entrada.nextLine();
            if (nomeProdutoVenda.equals("fim")) break;

            if (estoque.containsKey(nomeProdutoVenda)) {
                int quantidadeVenda = Integer.parseInt(entrada.nextLine());
                System.out.println(nomeProdutoVenda + " " + quantidadeVenda);
                estoque.put(nomeProdutoVenda, estoque.get(nomeProdutoVenda) - quantidadeVenda);
            } else {
                System.out.println(nomeProdutoVenda + " produto não encontrado");
            }
        }

        for (Map.Entry<String, Integer> produto : estoque.entrySet()) {
            System.out.println(produto.getKey() + " " + produto.getValue());
        }

        entrada.close();
    }
}



// QUESTÃO 6
import java.util.Scanner;
public class CorretorOrtografico {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        int n = Integer.parseInt(entrada.nextLine());
        String[] palavras = new String[n];
        
        for (int i = 0; i < n; i++) {
            palavras[i] = entrada.nextLine();
        }
        
        String palavra = entrada.nextLine();
        
        if (noVetor(palavras, palavra)) {
            System.out.println("palavra correta");
        } else {
            System.out.println("palavra incorreta");
            String sugestao = sugestaoPorTransposicao(palavras, palavra);
            if (sugestao != null) {
                System.out.println(sugestao + "?");
            } else {
                System.out.println("nenhuma sugestão");
            }
        }
        
        entrada.close();
    }

    private static boolean noVetor(String[] palavras, String palavra) {
        for (String p : palavras) {
            if (p.equals(palavra)) {
                return true;
            }
        }
        return false;
    }

    private static String sugestaoPorTransposicao(String[] palavras, String palavra) {
        for (int i = 0; i < palavra.length() - 1; i++) {
            String palavraTransposta = trocarLetras(palavra, i, i + 1);
            if (noVetor(palavras, palavraTransposta)) {
                return palavraTransposta;
            }
        }
        return null;
    }

    private static String trocarLetras(String palavra, int i, int j) {
        char[] letras = palavra.toCharArray();
        char temp = letras[i];
        letras[i] = letras[j];
        letras[j] = temp;
        return new String(letras);
    }
}



// QUESTÃO 7
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
public class SiglasInternet {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        int n = Integer.parseInt(entrada.nextLine());
        Map<String, String> dicionario = new HashMap<>();
        
        for (int i = 0; i < n; i++) {
            String[] siglaSignificado = entrada.nextLine().split(" ");
            String sigla = siglaSignificado[0].toLowerCase();
            String significado = siglaSignificado[1];
            dicionario.put(sigla, significado);
        }

        String frase = entrada.nextLine();
        
        StringBuilder fraseTraduzida = new StringBuilder();
        String[] palavras = frase.split(" ");
        for (String palavra : palavras) {
            if (dicionario.containsKey(palavra.toLowerCase())) {
                fraseTraduzida.append(dicionario.get(palavra.toLowerCase())).append(" ");
            } else {
                fraseTraduzida.append(palavra).append(" ");
            }
        }
        System.out.println(fraseTraduzida.toString().trim());
        entrada.close();
    }
}
