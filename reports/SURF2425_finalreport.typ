#import "@preview/rubber-article:0.3.1": *
#set text(lang:"en")
#set smartquote(enabled: false)
// #import "@preview/unify:0.7.0": num,qty,numrange,qtyrange
// #set math.equation(numbering: "(1)")
#import "@preview/tablex:0.0.9": tablex, colspanx, rowspanx

#show: article.with(
  show-header: true,
  header-titel: "SURF Final Report - 2025",
  eq-numbering: "(1.1)",
  eq-chapterwise: true,
  bibliography: bibliography("refs.bib"),
  bib-titel: "References",
  lang: "en"
)


#maketitle(
  title: "Optimization of Experimental Parameters for probing sub-GeV Dark Matter by using Muon Beams at the Light Dark Matter eXperiment (LDMX).\n Final Report - SURF 2025",

  authors: ("Thuwaragesh Jayachandran",
    ),

  //date: datetime.today().display("[day]st [month repr:long] [year]"),
  date: "Mentors: Prof. Bertrand Echenard, Prof. David Hitlin 
  California Institute of Technology"

      
)

= Abstract

This project investigates the characteristics of a muon beam produced in electron-fixed target collisions to study dark sector physics with an experimental concept similar to the Light Dark Matter eXperiment (LDMX). Using the _Geant4_ simulation framework, we model interactions between an 8 GeV electron beam and a tungsten target to evaluate muon yield and background processes under varying target geometries. Additionally, we performed spatial and angular analysis of muon emission and background particle fluxes to inform
filtering strategies. We also performed numerical calculations based on the
characterization of the muon flux to understand the sensitivity of the experiment to various scenarios of new physics.

= Introduction

The Light Dark Matter eXperiment (LDMX) is a proposed experiment that aims to probe for sub-GeV dark matter through collisions of electron beam with a fixed target @LDMX:2018cma. By tracking of the incoming and outgoing particles to monitor their momenta, and precisely measuring the energy deposits using electromagnetic and hadronic calorimeters, the experiment will attempt to veto out all of known standard model processes. Any missing momentum or missing energy for which a standard model process cannot be attributed will be an indication of the existence of matter that is not predicted by the standard model -- which could possibly be dark matter.
 
Both the LDMX @LDMX:2018cma and $M^3$ @M3:2018 proposals advocate extending LDMX to use muon beams, motivated by their potential to address muon physics anomalies, probe muon-philic forces, and explore dark sectors that couple preferentially to second-generation Standard Model particles @MuonDM2017. Muons, unlike electrons, lose less energy via bremsstrahlung, enabling deeper penetration and higher interaction rates with dark sector mediators, and are thus well-suited for probing heavier dark matter candidates. Experimentally, muon beams offer significant advantages: bremsstrahlung backgrounds are suppressed by a factor of about $(m_e/m_mu)^2 approx 2 times 10^(-5)$, greatly reducing challenging backgrounds for LDMX calorimetry @LDMX:2018cma, and allow for percent-level momentum resolution with a magnetized target, collectively promising increased experimental sensitivity over electron beams.

The ability to generate a well-characterized muon beam is critical for achieving the above mentioned goals. One promising method is to directly generate muons in electron-fixed target collisions. When a high-energy electron beam strikes a dense material such as tungsten, it produces pairs of charged muons. A key challenge is the efficiency of muon production. For comparison, a 4 GeV electron beam has a muon production rate of only around $10^(-6)$ when using the LDMX fixed target @LDMX:2018cma. Indeed, muons lose much energy compared to electrons when penetrating through targets of same radiation lengths @M3:2018. Thus, it is essential to optimize the target geometry to maximize the muon yield while minimizing background processes. It is also important to characterize the energy and angular distributions of the produced muons and the background particles to inform the design of the downstream beamline and detector systems.

The results were positive suggesting that the initial guess of the target geometry was close to optimal. The resulting muon yield of approximately $10^13$ muons over the expected experiment lifetime was identified to be sufficient for the LDMX conditions to probe new physics as expected. 

= Method and Results

Our approach to the study involved the following steps:

1. Setting up the _Geant4_ simulation framework to model the interactions between an 8 GeV electron beam and a tungsten target.
2. Understanding the various physical processes involved in muon production.
3. Analyzing the effects of target thickness on the muon yield and  the background yield.
4. Characterization of the energy and angular distributions of the produced particles under the optimized geometry.
5. Performing numerical calculations based on the characterization of the muon flux to understand the sensitivity of the experiment.

== Setup

We utilized the _Geant4_ simulation framework to model the interactions between an 8 GeV electron beam and a tungsten target. The target was initially modeled as a cube with a side length of 10 cm. To replicate LDMX conditions, the beam is simulated to emit single 8 GeV electrons per event from a randomly chosen point within a 3 cm $times$ 8 cm area, aimed at the center of the cube’s face. Detectors were programmed in order to record the properties of all the particles coming out of the target. Throughout the project, slight modifications were made to this initial setup, and these are discussed in the corresponding sections below. 


#figure(
  caption: [Target geometry used for the study. The target is a square based prism with a side length of 10 cm. The electron beam is incident perpendicularly on the center of a square face and has a 3 cm $times$ 8 cm area. Target thickness is defined as the length of the side along the beam direction.],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_target.jpg", width: 60%),
    )
) <setup>

The target is centred at the origin and the incoming beam direction is taken to be the $z$-axis. For each outgoing particle, the angle that its momentum vector makes with the $z$-axis is defined as its polar angle $theta_p$. We expect the muons to be produced with small polar angles ($theta_p<10 degree$) and with high momenta ($p>2$ GeV). Such cuts will make the muons sufficiently energetic and also easen the process of collimating them into a beam for the downstream detectors. As we shall see with numerical evidence below, both these conditions are complementary to each other since conservation of momentum required that the high energy muons be produced at small polar angles.

== Physical processes of muon production

There are two main processes through which muons can be produced in our setup of electron - tungsten collisions: pion decays and trident processes. Pion decays are represented by the following equations,

$
  pi^+ arrow mu^+ + nu_mu\
  pi^- arrow mu^- + overline(nu)_mu
$
The trident processes are represented by,
$
  e^- + N arrow e^- + N + mu^+ + mu^-
$
where $N$ represents a nucleus in the tungsten target.

Due to their higher cross sections, pion decays proved to be the dominant source of muons in the setup, producing around 2300 muons on average for runs of $10^6$ events (i.e. $10^6$ electrons incident on the target). The trident processes produced only 10 muons on average for the same runs. However, as shown in @muon_types below, the number of muons that are emitted out of the target turned to be almost same for both processes. Further analysis of the pion decay process within the target showed that an overwhelming majority of the pions decay into muons only when they are at rest. This results in most of such muons being emitted with a fixed kinetic energy of around 4.2 MeV, which is why most of them are not able to escape the target. Even the ones that are emitted out of the target are not energetic enough and are emitted at large polar angles, making them unsuitable for our purposes.

#figure(
  caption: [Momentum vs polar angle distributions of muons produced from pion decays and from trident processes. Results are shown for a 1000 $times$ biased simulation with $10^6$ events.],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_mu_p_vs_theta.png", width: 73%),
    )
) <muon_types>

The trident processes, on the other hand, produce muons that are energetic and are emitted at small polar angles. This is because the muons produced in these processes inherit a significant fraction of the momentum of the incoming electron beam. The high energetic electrons are able to transfer this energy into a virtual photon, which then produces the muon pair. 

Imposing a cut of $p>2$ GeV, we find that we obtain 2 muons per $10^6$ incoming electrons. While this is a promising yield for our purposes, it is essential to generate further statistics to confirm this result. Thus we decieded to bias the cross-section of the trident processes by a factor of $10^3$. This was achieved by enabling the `G4GenericBiasingPhysics` module and specifically biasing the `"GammaToMuPair"` process for gamma photons. This was also done in a way that the kinematics of the other processes are not altered. The setup in the following sections include this biasing.

== Target thickness optimization

We define the length of the side of the target that is along the incoming electron beam direction as the 'target thickness'. We expect that the target thickness will have a significant effect on the flux of all the outcoming particles. A thicker target would allow for more interactions, thus increasing the yield of any given particle. However, it would also cause more energy loss due to particle scattering and similar processes. These competing effects make it essential to identify the optimal thickness of the target that maximizes the muon yield. Since we also want to minimize the flux and energy of the background particles, a strategy would be to increase the target thickness as much as possible without sacrificing the muon yield. 

To study this effect, we simulated targets with thicknesses of 1 cm, 5 cm, 10 cm, 15 cm, and 20 cm. We kept the dimensions of the other two sides of the target fixed at 10 cm each. Left plot of @muon_prod below shows the cumulative number of muons produced as a function of their production point, which is expressed as a length into the target along the beam direction. Comparing the plots for 1 cm, 5 cm, and 10 cm thicknesses, it is clear that the muon production is saturated by 5 cm. This means that a 5 cm target thickness (within the set of target thicknesses that we tested) is sufficient enough to produce the maximum possible muon yield, keeping the other parameters fixed. The right plot of @muon_prod shows the rate of high energy muons coming out of the cube, expressed as muons per electron on target, as a function of the target thickness. Depending on the minimal momentum cut that is applied, the yield is maximized between 5 cm and 10 cm thicknesses. For higher thicknesses, even though the total number of muons produced increases, the number of high energy muons that are useful decreases due to the presence of extra tungsten. Both of these results suggest that a target thickness range of 5 cm to 10 cm might be optimal for our purposes.

#figure(
  caption: [Left: Cumulative distribution of muons as a function of their production point ($10^5$ events). Right: Rate of high energy muons coming out of the cube as a function of the target thickness. Results are for 1000 $times$ biased simulations.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/FINAL_mu_prod.png", width: 100%),
  image("images/FINAL_mu_rate.png", width: 100%),
    )
) <muon_prod>

We expect a similar behavior for the background particles as well. However, we want to minimize their yield as much as possible, as opposed to maximizing it as in the case of muons. We present the results obtained for electrons and positrons combined as a typical example of the background particles that we studied. We also studied photons, protons, neutrons, pions, and their corresponding antiparticles, but these results seemed to have a very similar behavior to that of electrons and positrons. We also define the 'cone region', as shown in @cone below, as the circular base of a cone with its apex at the center of the target and its axis along the beam direction. The cone is defined to have an half angle of $10 degree$ and a height of 1 m as shown. This region serves as an approximation of the opening that will let particles into the beamline in the actual experiment. Studying the flux of particles inside this region thus gives an estimate of the number of particles that will enter the beamline.

#figure(
  caption: [Definition of the 'cone region' used as a proxy for the beamline opening. The cone has its apex at the center of the target and axis along the electron beam direction.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/FINAL_cone.jpg", width: 60%),
    )
) <cone>

@electron_energy below shows the kinetic energy distributions of electrons (and positrons) entering the cone region, for different target thicknesses. It is clear that as the thickness is increased, the number and the kinetic energies of the electrons decrease significantly. Thus, it is beneficial to increase the target thickness as much as possible to minimize the background flux. The results are very similar for photons and protons as well, although their numbers are very different.

#figure(
  caption: [Distributions of kinetic energies of electrons and positrons entering the cone region for different target thicknesses ($10^4$ events). ],
  grid(
    columns:2,
    gutter:0mm,
    image("images/FINAL_e_E_dist.png", width: 75%),
    )
) <electron_energy>

Pions and neutrons are also very important background particles to consider since they can interfere with the experimental setup and also be hard to be eliminated from the setup. The analysis of pions ensured that almost pions enter the cone region for any thicknesses. For neutrons, we observed that their numbers (entering the cone region), peaks around 5 cm and then drops sharply. This suggests that a target thickness of 10 cm is to be preferred over a 5 cm one, since it significantly minimizes the neutron background with very slight sacrifice of the muon yield.

#figure(
  caption: [Rate of neutrons entering the cone region as a function of the target thickness],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_neutrons.png", width: 75%),
    )
) <neutrons>

== Characterization of the fluxes for muons and background particles

We now present the characterization of the muon flux produced from an optimized target geometry. Based on the above results, we selected a target thickness of 10 cm for this purpose. @muon_dist below shows both the cumulative momentum and angular distributions of the muons entering the cone region for this target geometry. The latter plot is also shown for 1 cm and 5 cm target thicknesses for comparison. For the angular distributions, we present the cumulative muon counts as a function of the half-angle of the cone region. The angular distribution shows that most of the muons are emitted at small polar angles, with around 90% of them being within a cone of half-angle of $5 degree$. The momentum distribution presents information that can be used if we were to use a different minimum momentum cut for the muons in our upcoming calculations. For example, if we were to use a cut of $p>3$ GeV instead of $p>2$ GeV, we would have a rate of 1.334 muons per $10^6$ electrons.

#figure(
  caption: [Left: Reversed cumulative distribution of muon momenta ($10^6$ events). Right: Number of muons with $p>2$ GeV entering the cone region as a function of the half-angle of the cone ($10^5$ events). Results are 1000 $times$ biased.],
  grid(
    columns:2,
    gutter:0mm,
    image("images/FINAL_mu_mom_dist.png", width: 108%),
  image("images/FINAL_mu_ang_dist.png", width: 100%),
    )
) <muon_dist>

In @electron_dist below, we present a similar angular distribution for the electrons. Here we present the cumulative electron counts as a fraction of the cumulative muon counts, for the corresponding half angle of the cone region. This plot shows that the ratio of electrons to muons decreases significantly as we decrease the half-angle of the cone region. Therefore, it is beneficial to have a small opening angle for the beamline to minimize the electron background, while also having a saturated muon yield.

#figure(
  caption: [Ratio of cumulative electron counts to cumulative muon counts entering the cone region as a function of the half-angle of the cone ($10^5$ events, unbiased). ],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_e_ang_dist_1.png", width: 93%),
  image("images/FINAL_e_ang_dist_2.png", width: 65%),
    )
) <electron_dist>

== Sensitivity calculations <sensitivity>


Given the energy distribution of the produced muons and and their total yield, we can estimate the sensitvity of the experiment under some assumptions. We consider a scenario in which the experiment would utilize muons of kinetic energy of 3 GeV or higher that go inside a cone region of half-angle $10 degree$. Summing up the bins from @muon_energy, we find that the rate of such muons is 1.44 per $10^6$ electrons on target. The electron beam at the Stanford Linear Accelerator produces pulses of $10^5$ electrons at 1 MHz.  We can thus perform the following calculation as an order of magnitude estimate for the total number of muons produced over the expected lifetime of the experiment, which is taken to be 4 years.
$
  N_mu &approx 1.44 dot 10^(-6)  text(" muons electrons")^(-1) dot 10^5 text(" electrons cycle")^(-1) dot 10^6 text(" cycles s")^(-1) dot  10^7 text(" s yr")^(-1) dot  4 text(" yr")\
  &approx 10^(13) text(" muons")
$ 
We further assume that the produced muons then are incident on an LDMX target made of tungsten with 50 radiation lengths ($X_0$). The number density of tungsten is taken to be $n_W = 6 dot 10^22 text(" cm")^(-3)$ and the radiation length is taken to be $X_0=0.35 text("cm")$.

#figure(
  caption: [Kinetic energy distribution of muons with kinetic energy $E_k>=3$ GeV entering the cone region for the optimized target geometry (10 cm thickness, $10^5$ events, 1000 $times$ biased). ],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_cone_muons_E.png", width: 75%),
    )
) <muon_energy>


With these estimates, we can use the differential cross section equations presented in @M3:2018 to calculate the cross sections for producting either a scalar of a vector particle from a muon (or antimuon)-tungsten nucleus interaction as below:
$
  mu + N arrow mu + N + S\
  mu + N arrow mu + N + V
$
The differential equations are given as follows, separately for the scalar ($S$) and vector ($V$) cases:
#import "@preview/diverential:0.2.0": *
$
  (frac( d sigma,d x))_S &approx frac(g_S^2 alpha^2, 4 pi) chi_S beta_S beta_mu frac(x^3[m_mu^2(3x^2-4x+4)+2 m_S^2(1-x)],[m_S^2(1-x)+m_mu^2x^2])\
  (frac( d sigma,d x))_V &approx frac(g_V^2 alpha^2, 4 pi) chi_V beta_V beta_mu frac(2x[x^2 m_mu^2(3x^2-4x+4)-2 m_V^2(x^3 -4 x^2+6x-3)],[m_V^2(1-x)+m_mu^2x^2])\

$<differential_cross_secs>
where, $E_text("beam")$ and $m_mu$ are the energy and mass of the incoming muon, $E_(S,V)$ and $m_(S,V)$ are the energy and mass of the produced scalar or vector particle, and $x=frac(E_(S,V),E_text)$. The coupling strengths are given by $g_(S,V)$. Furthermore, $beta_u = sqrt(1-m_mu^2/E_text("beam")^2)$ and $beta_(S,V)=sqrt(1-m_(S,V)^2/(x E_text("beam"))^2)$. The $chi_(S,V)$ are also approximated using the following equations from the same reference @M3:2018:
$
  chi_(S,V) = integral_(t_text("min"))^(t_text("max"))  d t frac(t-t_text("min"),t^2) G_2(t) approx integral_(m_(S,V)^4/(4 E_text("beam")^2))^(m_(S,V)^2+m_mu^2)  d t frac(t-m_(S,V)^4/((4 E_text("beam")^2)),t^2) G_2(t)
$
with $G_2$ being the target form factor, which we obtained from @MuonDM2017.

To obtain the total cross sections, @differential_cross_secs need to be integrated over $x$ within the corresponding limits. The higher limit is given by the maximum energy that the produced particle can have, which happens when it takes all the possible energy from the incoming muon while the muon comes to rest. Thus, $x_text("max")=(E_text("beam") - m_mu)/(E_text("beam"))= 1-m_mu/E_text("beam")$. The lower limit is determined by the minimum energy required for the produced particle so that it can be distinguished from the background in the experimental setup. As suggested by the $M$^3 proposal, we chose $x_text("min") in {1/3,1/2,2/3}$. The integration then will result in the total cross sections $sigma_(S,V)$ as functions of the massses $m_(S,V)$, coupling strengths $g_(S,V)$ and the beam energy $E_text("beam")$.

#figure(
  caption: [Top: Expected number of produced scalar or vector particles as a function of their mass for different $x_text("min")$ values, taking $g_(S,V)=1$. Bottom: Coupling strengths required to produce  1 scalar or vector particle as a function of their mass for different $x_text("min")$ values. Above plots assume $N_mu = 10^(13)$, $l=50 X_0$, and the energy distriubution presented in @muon_energy],
  grid(
    columns:1,
    gutter:0mm,
    image("images/FINAL_N.jpg", width: 100%),
    image("images/FINAL_g.jpg", width: 100%),
    )
) <Ng>

As shown in @muon_dist, the useable muons form a distribution of energies. Therefore, we bin these energies into a binwidth of 500 MeV and take the midpoint of each bin as the representative energy for that bin. Then, we calculate $sigma_(S,V)$ for each bin and take a weighted average over all the bins to obtain $sigma_((S,V),text("weighted"))$. Finally, we can calculate the expected number of produced scalar or vector particles using the following equation:
$
  N_(S,V)(g_(S,V),m_(S,V)) = N_mu  n_W  l sigma_((S,V),text("weighted"))(g_(S,V), m_(S,V))
$ 
where $l=50 X_0$ is the length of the tungsten target. We present the results of these calculations for the different values of $x_text("min")$ and taking $g_(S,V)=1$ in the top plot of @Ng below. In the bottom plot of @Ng, we have inverted the equations to calculate the coupling strengths $g_(S,V)$ required to produce at least 1 scalar or vector particle ($N_(S,V)(g_(S,V),m_(S,V))=1$). Both these plots are presented as functions of the mass of the produced particle, which is unknown.


From the plots, it is clear that for $m_(S,V)<100 $ MeV, the experiment is sensitive to coupling strengths as low as $10^(-5)$ for both scalar and vector cases. This sensitivity decreases for higher masses, reaching around $10^(-4)$ for masses close to 1 GeV. But in this domain, we also expect the calculations to be less accurate @M3:2018, since $E_text("beam")$ becomes comparable to the mass thresholds of the produced particles. To estimate the $N_(S,V)$ for different $g_(S,V)$ values, we only need to multiply the above results by $g_(S,V)^2$, since $N_(S,V) prop sigma_(S,V) prop g_(S,V)^2$ from @differential_cross_secs.






= Future work and conclusions

Several parameters used throughout this study were initial estimates that were used as placeholders. The half-angle of the cone region and the distance from the target to the beam line opening depend on the actual experimental setup and need to be updated once more information becomes available. Similarly, the minimum muon momentum cut that would be necessary to ensure a clean signal needs to be determined through further simulations and experimental data. Furthermore, the $x_text("min")$ values will need to be revisited with simulations from the LDMX setup. We would also need some estimates of the coupling strengths $g_(S,V)$ from theoretical models to better understand the sensitivity of the experiment.

For obvious reasons, changes to these numbers will affect the final sensitivity calculations, and also our result of the optimized target thickness being between 5 cm and 10 cm. However, this study lays as a solid baseline for this future work, since once can easily reuse this simulation framework just by updating the parameters. From the initial estimates used here for the study, we conclude that it is a promising approach to use electron-tungsten target collisions in order to generate a muon beam for probing sub-GeV dark matter at LDMX. 

= Acknowledgements

I would like to express my sincere gratitude to my mentors, Prof. Bertrand Echenard and Prof. David Hitlin, and their group for their support and guidance throughout this project. I am also thankful to the William H. and Helen Lang SURF Fellowship for providing me with the funding to undertake this research.