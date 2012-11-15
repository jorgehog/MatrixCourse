<?php include "config.php"; ?>
<?php include "../../includes/inc_functions.php"; ?>
<?php include "../../includes/inc_header.php"; ?>

<div class="slides">
	
	$
	\renewcommand{\vec}{\mathbf}
	\newcommand{\mat}{\mathbf}
	$
	
<section>
		<h1>Unsymmetric Eigensolvers</h1><br>
		<h3>The Unsymmetric Eigenvalue Problem</h3>
		<br>
		<br>
		<div><?php echo date("l, j F Y") ?></div>
	</section>
	
	<!---------------------------------------- New Slide ------------------------------------->
	
	<section>
		<section>
			
			<h1>Looking behind the curtains</h1><br>
			<h3>Revealing the underlying problem</h3>
			
		</section>

		<section>
		<h3>Unsymmetric matrices</h3>
			<p>
				Given real matrices, unsymmetry is the case when
				\begin{equation}
				\mat{A}^T \ne \mat{A}.
				\end{equation}

				Generalizable to complex matrices; <i>non-Hermitian</i> if,
                \begin{equation}
                \mat{A}^\dagger  \ne \mat{A},
                \end{equation}
                where $\mat{A}^\dagger $ denotes the conjugate transpose.
			</p>
		</section>

		<section>
			<h3> Unitary decompositions </h3><br>
			
			<p> 
				$\mat{A} = \mat{Q}^\dagger \mat{\tilde{A}}\mat{Q}$
            </p>
            
            <p class="fragment">
				The acting of a unitary matrix $\mat Q$ as above is called a <span style="color:#FF0000">similarity transformation</span>; $A$ is similar to $\tilde{A}$.
            </p>
            
            <p class="fragment">
				By definition $Q^\dagger Q = \mat I \longrightarrow$ $|\det(\mat Q)|^2 = 1$<br><br>
			</p>
			
            <p class="fragment">	
				The determinant is <span style="color:#FF0000">conserved</span> under a similarity transform.
            </p>
           
		</section>

        <section>
			
			<h3>The problem</h3>
			
            <p>
                \begin{equation}
                \mat{A} \vec{v} = \lambda\mat{v}
                \end{equation}

                Eigenvalues are the roots of the <i>characteristic polynomial</i>
                \begin{equation}
                P(\lambda) = \det (\mat{A} - \lambda\mat{I_n}) = c_0 + c_1\lambda + c_2\lambda^2 + ... + \lambda^n
                \end{equation}
            </p>
                    
            <p class="fragment">
				Conservation of determinants in similarity transformations implies the conservation of the characteristic polynomial.<br>
			</p>
			
			<p class="fragment"> 
				<span style="color:#FF0000">Similarity transformations conserve the eigenvalues</span>.
			</p> 
            
		</section>
           
		<section>
			
			<h4 align="left">Proof:</h4>
			
			\begin{eqnarray}
			\tilde{P}(\lambda) &=& \det (\mat{Q}^\dagger \mat{AQ} - \lambda\mat{I})           \\
						       &=& \det (\mat{Q}^\dagger \mat{AQ} - \lambda\mat{Q}^\dagger \mat{Q})         \\
                               &=& \det (\mat{Q}^\dagger (A - \lambda\mat{I})\mat{Q}^\dagger ) 		  \\
                               &=& \det (\mat{Q}^\dagger \mat{Q})\det (\mat{A} - \lambda\mat{I}) \\
                               &=& P(\lambda)
			\end{eqnarray}
           
		</section>
                
		<section>
			
			<h3>The solution</h3><br>
			
			<p>
				Unitary decompositions to matrices with revealing eigenvalues. 
			</p>
			
			<p class="fragment">
				E.g. diagonalization:
				\begin{equation}
				\mat A = \mat{P}^{-1}\mat{DP},\qquad \mat D_{ij} = \lambda_{i}\delta_{ij}, \qquad \vec P_{:j} = \vec v_j
				\end{equation}
			</p>
			
			<p class="fragment">
				$\lambda_i = \Big(\mat P \mat A \mat P^{-1}\Big)_{ii}$
			</p>
			
			<p class="fragment">
				Note: Requires a complete set of eigenvectors. <span style="color:#FF0000">Not the general case for unsymmetric matrices</span>.
			</p>
				
		</section>
	</section>
	
	<!---------------------------------------- New Slide ------------------------------------->
	
	<section>      
		<section>
			
			<h1>Generalizations</h1><br>
			<h3>Based on the symmetric case</h3>
				
		</section>
           
        <section>
			<p>
				Expanding $\mat A \in \mathbb{C}$ in Hermitian matrices
			</p>
           
			<p class="fragment">
				\begin{eqnarray}
				\mat A &=& \frac{1}{2}\Big(\mat A + \mat A^\dagger \Big) + i\Big(-\frac{1}{2}i\left(A - A^\dagger \right)\Big) \\
					   &\equiv& \mat B + i\mat C
				\end{eqnarray}
			</p>
           
			<p class="fragment">
					$\mat B$ and $\mat C$ both have complete sets of eigenvectors, however, these are <span style="color:#FF0000">not necessarily equal</span>.
			</p>
           
		</section>
           
		<section>
			<p>
				$\mat A$, $\mat B$ and $\mat C$ all share eigenvectors if<br><br>
			</p>

			<p class="fragment">
				$[\mat A, \mat B] = [\mat A, \mat C] = [\mat B, \mat C] = \mat 0$
			</p>
		   
			<p class="fragment">
				$$\Downarrow$$
				$[\mat A, \mat A^\dagger ] = \mat 0$
			</p>

			<p class="fragment"><br>
				All <span style="color:#0000FF">normal</span> matrices are diagonalizable matrices.
			</p>
	
		</section>
                
		<section>
			<h3 align="left">Alternative unitary decomposition: <span style="color:#0000FF">Schur</span></h3>
			
			<p class="fragment">$\mat A = \mat{Q}^\dagger \mat S\mat{Q}$</p>
			
			<p class = "fragment">
				\begin{equation}
				\mat S = \mat{Q}\mat A\mat{Q}^\dagger  = \left( 
				\begin{array}{cccccc}
				\mat S_{11} & \times & \times &  \times & \cdots &  \times \\
				0           & \ddots & \times &  \times & \cdots &  \times  \\
				0           &  0     &        &  \times & \cdots &  \times   \\
				\vdots      & \vdots & \ddots &  \ddots &        &  \vdots    \\
				0           & 0      &        &         &        &  \times	   \\
				0           & 0	     & \cdots & 	0	& 0	     &  \mat S_{nn} \\
				\end{array} \right) 
				\end{equation} 
				where $\lambda_j=\mat S_{ii}$ (not uniquely ordered).
			</p>
				
		</section>
			
		<section>
			<p>
				$$\mat S = \mat D + \mat N,\qquad \mat Q = [\vec q_1, ..., \vec q_n]$$
				where $\mat N$ is strictly upper triangular and  $\vec q_k$ is called a <i>Schur vector</i>.
			</p>
			
			<p class="fragment">
				$$ \mat N_{:k}=\vec 0 \longrightarrow \mat A \vec q_k = \lambda_i\vec q_k$$
			</p>
		
			<p class="fragment">
				Can be shown that $\mat N = \mat 0$ for all normal matrices.
			</p>
			
			<p class="fragment">
				<span style="color:#FF0000">Diagonalization is a special case of Schur decomposition where the matrix at hand is normal.</span>
			</p>
			
		</section>
	</section>
	
	<!---------------------------------------- New Slide ------------------------------------->
	
	<section>
		<section>
			
			<h1>Power iterations</h1>
			<h3>with focus on QR-iterations</h3>
		
		</section>
    
    
    
    
    </section>

</div>

<?php include "../../includes/inc_footer.php"; ?>
