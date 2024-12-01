// Questão 1
import java.util.Scanner;
public class Impressora {
    public String modelo;
    public String cor;
    public String tipoPapel;
    public boolean bluetooth = true;
    public boolean wifi = true;
    public boolean colorida = true;
    public boolean ligada = false;
    public boolean papel = true;
    public boolean digitalizadora = true;
    public boolean copiadora = false;

    public void ligar() {
        if (!ligada) {
            System.out.println("ligando...");
            ligada = true;
        }
    }

    public void desligar() {
        if (ligada) {
            System.out.println("desligando...");
            ligada = false;
        }
    }

    public void imprimir() {
        if (ligada) {
            if (papel) {
                System.out.println("imprimindo...");
            } else {
                System.out.println("sem papel");
            }
        } else {
            System.out.println("impressora desligada");
        }
    }

    public void digitalizar() {
        if (ligada) {
            if (digitalizadora) {
                System.out.println("digitalização sendo realizada...");
            } else {
                System.out.println("não é possível digitalizar");
            }
        } else {
            System.out.println("impressora desligada");
        }
    }

    public void copiar() {
        if (ligada) {
            if (copiadora) {
                System.out.println("cópia sendo realizada...");
            } else {
                System.out.println("não é possível copiar");
            }
        } else {
            System.out.println("impressora desligada");
        }
    }

    public void status() {
        System.out.println(modelo);
        System.out.println(cor);
        System.out.println(tipoPapel);
        System.out.println(bluetooth ? "bluetooth on" : "bluetooth off");
        System.out.println(wifi ? "wifi on" : "wifi off");
        System.out.println(colorida ? "impressão colorida" : "impressão preto e branco");
        System.out.println(ligada ? "impressora on" : "impressora off");
        System.out.println(papel ? "tem papel" : "não tem papel");
        System.out.println(digitalizadora ? "digitalizadora on" : "digitalizadora off");
        System.out.println(copiadora ? "copiadora on" : "copiadora off");
    }
}


public class UsaImpressora {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        Impressora impressora = new Impressora();

        impressora.modelo = entrada.next();
        impressora.cor = entrada.next();
        impressora.tipoPapel = entrada.next();

        impressora.status();

        impressora.ligar();
        impressora.digitalizar();
        impressora.copiar();
        impressora.desligar();
        impressora.imprimir();

        entrada.close();
    }
}

// Questão 2
import java.util.Scanner;
class Retangulo {
    private int comprimento = 1;
    private int largura = 1;

    public void setComprimento(int comprimento) {
        if (comprimento > 0 && comprimento < 20) {
            this.comprimento = comprimento;
        }
    }

    public void setLargura(int largura) {
        if (largura > 0 && largura < 20) {
            this.largura = largura;
        }
    }

    public int getComprimento() {
        return comprimento;
    }

    public int getLargura() {
        return largura;
    }

    public int calcularPerimetro() {
        return 2 * (comprimento + largura);
    }

    public int calcularArea() {
        return comprimento * largura;
    }
}

public class Formas {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        Retangulo retangulo1 = new Retangulo();
        int comprimento1 = entrada.nextInt();
        int largura1 = entrada.nextInt();
        retangulo1.setComprimento(comprimento1);
        retangulo1.setLargura(largura1);

        Retangulo retangulo2 = new Retangulo();
        int comprimento2 = entrada.nextInt();
        int largura2 = entrada.nextInt();
        retangulo2.setComprimento(comprimento2);
        retangulo2.setLargura(largura2);

        System.out.printf("%d %d %d %d%n",
                retangulo1.getComprimento(),
                retangulo1.getLargura(),
                retangulo1.calcularPerimetro(),
                retangulo1.calcularArea());

        System.out.printf("%d %d %d %d%n",
                retangulo2.getComprimento(),
                retangulo2.getLargura(),
                retangulo2.calcularPerimetro(),
                retangulo2.calcularArea());

        entrada.close();
    }
}


// Questão 3
import java.util.Scanner;
class Temperatura {
    private double temperatura;
    
    public Temperatura(double temperatura) {
        this.temperatura = temperatura;
    }
    
    public void CelsiusFahrenheit() {
        this.temperatura = this.temperatura * 9.0 / 5.0 + 32;
    }
    
    public void FahrenheitCelsius() {
        this.temperatura = (this.temperatura - 32) * 5.0 / 9.0;
    }
    
    public String toString() {
        return String.format("temperatura: %.1f graus", temperatura);
    }
}

public class Converte {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        double entradaTemperatura = entrada.nextDouble();
        
        Temperatura temp = new Temperatura(entradaTemperatura);
        
        temp.CelsiusFahrenheit();
        System.out.println(temp + " fahrenheit");
        
        temp.FahrenheitCelsius();
        System.out.println(temp + " celsius");
        
        entrada.close();
    }
}


// Questão 4
import java.util.Scanner;
class Conta {
    private int numeroConta;
    private String nomeCliente;
    private double saldo;
    private int senha;

    public Conta(int numeroConta, int senha, String nomeCliente, double saldo) {
        this.numeroConta = numeroConta;
        this.senha = senha;
        this.nomeCliente = nomeCliente;
        this.saldo = saldo;
    }

    public int getNumeroConta() {
        return numeroConta;
    }

    public String getNomeCliente() {
        return nomeCliente;
    }

    public double getSaldo(int senha) {
        if (this.senha == senha) {
            return saldo;
        } else {
            return -1;
        }
    }

    public boolean sacar(double valor, int senha) {
        if (this.senha == senha && valor > 0 && valor <= saldo) {
            saldo -= valor;
            return true;
        }
        return false;
    }

    public boolean depositar(double valor, int senha) {
        if (this.senha == senha && valor > 0) {
            saldo += valor;
            return true;
        }
        return false;
    }

    public boolean transferir(double valor, int senha, Conta conta2) {
        if (this.senha == senha && valor > 0 && valor <= saldo) {
            saldo -= valor;
            conta2.depositar(valor, conta2.senha);
            return true;
        }
        return false;
    }
}

public class Banco {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        int numeroConta1 = entrada.nextInt();
        int senhaConta1 = entrada.nextInt();
        String nomeCliente1 = entrada.next();
        double saldoConta1 = entrada.nextDouble();
        Conta conta1 = new Conta(numeroConta1, senhaConta1, nomeCliente1, saldoConta1);

        int numeroConta2 = entrada.nextInt();
        int senhaConta2 = entrada.nextInt();
        String nomeCliente2 = entrada.next();
        double saldoConta2 = entrada.nextDouble();
        Conta conta2 = new Conta(numeroConta2, senhaConta2, nomeCliente2, saldoConta2);

        int op;
        do {
            op = entrada.nextInt();
            switch (op) {
                case 1:
                    int senhaSaldo = entrada.nextInt();
                    double saldo = conta1.getSaldo(senhaSaldo);
                    if (saldo != -1) {
                        System.out.printf("%.2f\n", saldo);
                    } else {
                        System.out.println("senha incorreta");
                    }
                    break;
                case 2:
                    double valorSaque = entrada.nextDouble();
                    int senhaSaque = entrada.nextInt();
                    if (conta1.sacar(valorSaque, senhaSaque)) {
                        System.out.println("saque realizado");
                    } else {
                        System.out.println("saque não realizado");
                    }
                    break;
                case 3:
                    double valorDeposito = entrada.nextDouble();
                    int senhaDeposito = entrada.nextInt();
                    if (conta1.depositar(valorDeposito, senhaDeposito)) {
                        System.out.println("depósito realizado");
                    } else {
                        System.out.println("depósito não realizado");
                    }
                    break;
                case 4: 
                    String nomeDestino = entrada.next();
                    if (nomeDestino.equals(conta2.getNomeCliente())) {
                        double valorTransferencia = entrada.nextDouble();
                        int senhaTransferencia = entrada.nextInt();
                        if (conta1.transferir(valorTransferencia, senhaTransferencia, conta2)) {
                            System.out.println("transferência realizada");
                        } else {
                            System.out.println("transferência não realizada");
                        }
                    } else {
                        System.out.println("nenhum usuário encontrado");
                    }
                    break;
                case 5:
                    break;
                default:
                    System.out.println("Opção inválida");
            }
        } while (op != 5);

        entrada.close();
    }
}

// Questão 5
import java.util.Scanner;
class Circulo {
    private int x, y, raio;
    public static final double PI = 3.14159;

    public Circulo(int x, int y, int raio) {
        this.x = x;
        this.y = y;
        this.raio = raio;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getRaio() {
        return raio;
    }

    public void setRaio(int raio) {
        this.raio = raio;
    }

    public double circunferencia() {
        return 2 * PI * raio;
    }
}

// Antigo
public class TestaCirculo {
    public static void main (String[]) args) {
        Circulo circulol, circu102, circu103;
        circulol = new Circulo (3, 3, 1);
        circulo2 = new Circulo (2, 1, 4);
        circulo3 = circulo1 ;// mesmo objeto

        System.out.println(circulo1.getX() + " " + circulo1.getY());
        System.out.println(circulo2.getX() + " " + circulo2.getY());
        System.out.println(circulo3.getX() + " " + circulo3.getY());
    
        int circulo = (int) circulo1.circunferencia();
        System.out.print(circulo1.getRaio()); // raio do circulo1
        System.out.print(" " + circulo); // circunferência do circulo1
    }
}

// Novo
public class TestaCirculo {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        Circulo[] vetor1 = new Circulo[3];
        for (int i = 0; i < 3; i++) {
            int x = entrada.nextInt();
            int y = entrada.nextInt();
            int raio = entrada.nextInt();
            vetor1[i] = new Circulo(x, y, raio);
        }

        Circulo[] vetor2 = vetor1;

        Circulo[] vetor3 = new Circulo[3];
        for (int i = 0; i < 3; i++) {
            vetor3[i] = new Circulo(vetor1[i].getX(), vetor1[i].getY(), vetor1[i].getRaio());
        }

        for (int i = 0; i < 3; i++) {
            int novoRaio = entrada.nextInt();
            vetor1[i].setRaio(novoRaio);
        }

        System.out.println("vetor1:");
        for (Circulo c : vetor1) {
            System.out.printf("%d %d %d%n", c.getX(), c.getY(), c.getRaio());
        }

        System.out.println("vetor2:");
        for (Circulo c : vetor2) {
            System.out.printf("%d %d %d%n", c.getX(), c.getY(), c.getRaio());
        }

        System.out.println("vetor3:");
        for (Circulo c : vetor3) {
            System.out.printf("%d %d %d%n", c.getX(), c.getY(), c.getRaio());
        }

        entrada.close();
    }
}
